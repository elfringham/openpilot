#include <algorithm>
#include <cassert>
#include <csignal>
#include <iostream>
#include <map>
#include <string>

typedef void (*sighandler_t)(int sig);

#include "cereal/services.h"
#include "msgq/impl_msgq.h"
#include "msgq/impl_zmq.h"

std::atomic<bool> do_exit = false;
static void set_do_exit(int sig) {
  do_exit = true;
}

void sigpipe_handler(int sig) {
  assert(sig == SIGPIPE);
  std::cout << "SIGPIPE received" << std::endl;
}

static std::vector<std::string> get_services(std::string whitelist_str) {
  std::vector<std::string> service_list;
  for (const auto& it : services) {
    std::string name = it.second.name;
    bool in_whitelist = whitelist_str.find(name) != std::string::npos;
    if (name == "plusFrame" || name == "uiLayoutState" || !in_whitelist) {
      continue;
    }
    service_list.push_back(name);
    printf("Allowed service name is %s\r\n", name.c_str());
  }
  return service_list;
}

int main(int argc, char** argv) {
  signal(SIGPIPE, (sighandler_t)sigpipe_handler);
  signal(SIGINT, (sighandler_t)set_do_exit);
  signal(SIGTERM, (sighandler_t)set_do_exit);

  if (argc != 4) {
    std::cout << "Usage:" << std::endl;
    std::cout << "\tremote_sim_bridge (op|sim) (pub|sub) <remote IP address>" << std::endl;
    return -1;
  }
  bool local_ui = strcmp(argv[1], "op") == 0;
  bool local_pub = strcmp(argv[2], "pub") == 0;
  std::string ip = local_pub ? argv[3] : "127.0.0.1";
  std::string servicelist_ui_str = "carControl,controlsState,carParams";
  std::string servicelist_sim_str = "can,gpsLocationExternal,driverStateV2,peripheralState,roadCameraState,roadEncodeData,roadEncodeIdx,wideRoadCameraState,wideRoadEncodeData,wideRoadEncodeIdx";
  //std::string servicelist_sim_str = "can,pandaStates,accelerometer,gyroscope,gpsLocationExternal,driverStateV2,driverMonitoringState,peripheralState,roadCameraState,wideRoadCameraState";
  std::string servicelist_str = local_ui ? servicelist_ui_str : servicelist_sim_str;
  printf("ZeroMQ on IP address %s\r\n", ip.c_str());

  Poller *poller;
  Context *pub_context;
  Context *sub_context;
  if (local_pub) {  // republishes zmq debugging messages as msgq
    poller = new ZMQPoller();
    pub_context = new MSGQContext();
    sub_context = new ZMQContext();
  } else {
    poller = new MSGQPoller();
    pub_context = new ZMQContext();
    sub_context = new MSGQContext();
  }

  std::map<SubSocket*, PubSocket*> sub2pub;
  for (auto endpoint : get_services(servicelist_str)) {
    PubSocket * pub_sock;
    SubSocket * sub_sock;
    if (local_pub) {
      pub_sock = new MSGQPubSocket();
      sub_sock = new ZMQSubSocket();
    } else {
      pub_sock = new ZMQPubSocket();
      sub_sock = new MSGQSubSocket();
    }
    pub_sock->connect(pub_context, endpoint);
    sub_sock->connect(sub_context, endpoint, ip, false);

    poller->registerSocket(sub_sock);
    sub2pub[sub_sock] = pub_sock;
  }

  while (!do_exit) {
    for (auto sub_sock : poller->poll(100)) {
      Message * msg = sub_sock->receive();
      if (msg == NULL) continue;
      int ret;
      do {
        ret = sub2pub[sub_sock]->sendMessage(msg);
      } while (ret == -1 && errno == EINTR && !do_exit);
      assert(ret >= 0 || do_exit);
      delete msg;

      if (do_exit) break;
    }
  }
  return 0;
}
