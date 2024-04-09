#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_7459114665916083270);
void live_err_fun(double *nom_x, double *delta_x, double *out_7132705503742969874);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_5508521473895153696);
void live_H_mod_fun(double *state, double *out_587104994641019900);
void live_f_fun(double *state, double dt, double *out_2978642854143158247);
void live_F_fun(double *state, double dt, double *out_388375667706179161);
void live_h_4(double *state, double *unused, double *out_2316967131109145089);
void live_H_4(double *state, double *unused, double *out_4432159738179544458);
void live_h_9(double *state, double *unused, double *out_7982815944968852205);
void live_H_9(double *state, double *unused, double *out_6727365400265559688);
void live_h_10(double *state, double *unused, double *out_5085672873651168485);
void live_H_10(double *state, double *unused, double *out_3842366662318691362);
void live_h_12(double *state, double *unused, double *out_1420358811908403366);
void live_H_12(double *state, double *unused, double *out_1949098638863188538);
void live_h_35(double *state, double *unused, double *out_891526568328106016);
void live_H_35(double *state, double *unused, double *out_3601892989522542957);
void live_h_32(double *state, double *unused, double *out_2623478293943095803);
void live_H_32(double *state, double *unused, double *out_3580122557880242764);
void live_h_13(double *state, double *unused, double *out_2831171244995848302);
void live_H_13(double *state, double *unused, double *out_2133918316798641961);
void live_h_14(double *state, double *unused, double *out_7982815944968852205);
void live_H_14(double *state, double *unused, double *out_6727365400265559688);
void live_h_33(double *state, double *unused, double *out_2365850921752563680);
void live_H_33(double *state, double *unused, double *out_451335984883685353);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}