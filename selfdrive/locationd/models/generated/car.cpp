#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1099665464184721179) {
   out_1099665464184721179[0] = delta_x[0] + nom_x[0];
   out_1099665464184721179[1] = delta_x[1] + nom_x[1];
   out_1099665464184721179[2] = delta_x[2] + nom_x[2];
   out_1099665464184721179[3] = delta_x[3] + nom_x[3];
   out_1099665464184721179[4] = delta_x[4] + nom_x[4];
   out_1099665464184721179[5] = delta_x[5] + nom_x[5];
   out_1099665464184721179[6] = delta_x[6] + nom_x[6];
   out_1099665464184721179[7] = delta_x[7] + nom_x[7];
   out_1099665464184721179[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4420002132005042565) {
   out_4420002132005042565[0] = -nom_x[0] + true_x[0];
   out_4420002132005042565[1] = -nom_x[1] + true_x[1];
   out_4420002132005042565[2] = -nom_x[2] + true_x[2];
   out_4420002132005042565[3] = -nom_x[3] + true_x[3];
   out_4420002132005042565[4] = -nom_x[4] + true_x[4];
   out_4420002132005042565[5] = -nom_x[5] + true_x[5];
   out_4420002132005042565[6] = -nom_x[6] + true_x[6];
   out_4420002132005042565[7] = -nom_x[7] + true_x[7];
   out_4420002132005042565[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6269193584076680151) {
   out_6269193584076680151[0] = 1.0;
   out_6269193584076680151[1] = 0;
   out_6269193584076680151[2] = 0;
   out_6269193584076680151[3] = 0;
   out_6269193584076680151[4] = 0;
   out_6269193584076680151[5] = 0;
   out_6269193584076680151[6] = 0;
   out_6269193584076680151[7] = 0;
   out_6269193584076680151[8] = 0;
   out_6269193584076680151[9] = 0;
   out_6269193584076680151[10] = 1.0;
   out_6269193584076680151[11] = 0;
   out_6269193584076680151[12] = 0;
   out_6269193584076680151[13] = 0;
   out_6269193584076680151[14] = 0;
   out_6269193584076680151[15] = 0;
   out_6269193584076680151[16] = 0;
   out_6269193584076680151[17] = 0;
   out_6269193584076680151[18] = 0;
   out_6269193584076680151[19] = 0;
   out_6269193584076680151[20] = 1.0;
   out_6269193584076680151[21] = 0;
   out_6269193584076680151[22] = 0;
   out_6269193584076680151[23] = 0;
   out_6269193584076680151[24] = 0;
   out_6269193584076680151[25] = 0;
   out_6269193584076680151[26] = 0;
   out_6269193584076680151[27] = 0;
   out_6269193584076680151[28] = 0;
   out_6269193584076680151[29] = 0;
   out_6269193584076680151[30] = 1.0;
   out_6269193584076680151[31] = 0;
   out_6269193584076680151[32] = 0;
   out_6269193584076680151[33] = 0;
   out_6269193584076680151[34] = 0;
   out_6269193584076680151[35] = 0;
   out_6269193584076680151[36] = 0;
   out_6269193584076680151[37] = 0;
   out_6269193584076680151[38] = 0;
   out_6269193584076680151[39] = 0;
   out_6269193584076680151[40] = 1.0;
   out_6269193584076680151[41] = 0;
   out_6269193584076680151[42] = 0;
   out_6269193584076680151[43] = 0;
   out_6269193584076680151[44] = 0;
   out_6269193584076680151[45] = 0;
   out_6269193584076680151[46] = 0;
   out_6269193584076680151[47] = 0;
   out_6269193584076680151[48] = 0;
   out_6269193584076680151[49] = 0;
   out_6269193584076680151[50] = 1.0;
   out_6269193584076680151[51] = 0;
   out_6269193584076680151[52] = 0;
   out_6269193584076680151[53] = 0;
   out_6269193584076680151[54] = 0;
   out_6269193584076680151[55] = 0;
   out_6269193584076680151[56] = 0;
   out_6269193584076680151[57] = 0;
   out_6269193584076680151[58] = 0;
   out_6269193584076680151[59] = 0;
   out_6269193584076680151[60] = 1.0;
   out_6269193584076680151[61] = 0;
   out_6269193584076680151[62] = 0;
   out_6269193584076680151[63] = 0;
   out_6269193584076680151[64] = 0;
   out_6269193584076680151[65] = 0;
   out_6269193584076680151[66] = 0;
   out_6269193584076680151[67] = 0;
   out_6269193584076680151[68] = 0;
   out_6269193584076680151[69] = 0;
   out_6269193584076680151[70] = 1.0;
   out_6269193584076680151[71] = 0;
   out_6269193584076680151[72] = 0;
   out_6269193584076680151[73] = 0;
   out_6269193584076680151[74] = 0;
   out_6269193584076680151[75] = 0;
   out_6269193584076680151[76] = 0;
   out_6269193584076680151[77] = 0;
   out_6269193584076680151[78] = 0;
   out_6269193584076680151[79] = 0;
   out_6269193584076680151[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1825805570165161384) {
   out_1825805570165161384[0] = state[0];
   out_1825805570165161384[1] = state[1];
   out_1825805570165161384[2] = state[2];
   out_1825805570165161384[3] = state[3];
   out_1825805570165161384[4] = state[4];
   out_1825805570165161384[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1825805570165161384[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1825805570165161384[7] = state[7];
   out_1825805570165161384[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4195817935556502074) {
   out_4195817935556502074[0] = 1;
   out_4195817935556502074[1] = 0;
   out_4195817935556502074[2] = 0;
   out_4195817935556502074[3] = 0;
   out_4195817935556502074[4] = 0;
   out_4195817935556502074[5] = 0;
   out_4195817935556502074[6] = 0;
   out_4195817935556502074[7] = 0;
   out_4195817935556502074[8] = 0;
   out_4195817935556502074[9] = 0;
   out_4195817935556502074[10] = 1;
   out_4195817935556502074[11] = 0;
   out_4195817935556502074[12] = 0;
   out_4195817935556502074[13] = 0;
   out_4195817935556502074[14] = 0;
   out_4195817935556502074[15] = 0;
   out_4195817935556502074[16] = 0;
   out_4195817935556502074[17] = 0;
   out_4195817935556502074[18] = 0;
   out_4195817935556502074[19] = 0;
   out_4195817935556502074[20] = 1;
   out_4195817935556502074[21] = 0;
   out_4195817935556502074[22] = 0;
   out_4195817935556502074[23] = 0;
   out_4195817935556502074[24] = 0;
   out_4195817935556502074[25] = 0;
   out_4195817935556502074[26] = 0;
   out_4195817935556502074[27] = 0;
   out_4195817935556502074[28] = 0;
   out_4195817935556502074[29] = 0;
   out_4195817935556502074[30] = 1;
   out_4195817935556502074[31] = 0;
   out_4195817935556502074[32] = 0;
   out_4195817935556502074[33] = 0;
   out_4195817935556502074[34] = 0;
   out_4195817935556502074[35] = 0;
   out_4195817935556502074[36] = 0;
   out_4195817935556502074[37] = 0;
   out_4195817935556502074[38] = 0;
   out_4195817935556502074[39] = 0;
   out_4195817935556502074[40] = 1;
   out_4195817935556502074[41] = 0;
   out_4195817935556502074[42] = 0;
   out_4195817935556502074[43] = 0;
   out_4195817935556502074[44] = 0;
   out_4195817935556502074[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4195817935556502074[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4195817935556502074[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4195817935556502074[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4195817935556502074[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4195817935556502074[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4195817935556502074[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4195817935556502074[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4195817935556502074[53] = -9.8000000000000007*dt;
   out_4195817935556502074[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4195817935556502074[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4195817935556502074[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4195817935556502074[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4195817935556502074[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4195817935556502074[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4195817935556502074[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4195817935556502074[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4195817935556502074[62] = 0;
   out_4195817935556502074[63] = 0;
   out_4195817935556502074[64] = 0;
   out_4195817935556502074[65] = 0;
   out_4195817935556502074[66] = 0;
   out_4195817935556502074[67] = 0;
   out_4195817935556502074[68] = 0;
   out_4195817935556502074[69] = 0;
   out_4195817935556502074[70] = 1;
   out_4195817935556502074[71] = 0;
   out_4195817935556502074[72] = 0;
   out_4195817935556502074[73] = 0;
   out_4195817935556502074[74] = 0;
   out_4195817935556502074[75] = 0;
   out_4195817935556502074[76] = 0;
   out_4195817935556502074[77] = 0;
   out_4195817935556502074[78] = 0;
   out_4195817935556502074[79] = 0;
   out_4195817935556502074[80] = 1;
}
void h_25(double *state, double *unused, double *out_7471202214093873351) {
   out_7471202214093873351[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4899541032027007789) {
   out_4899541032027007789[0] = 0;
   out_4899541032027007789[1] = 0;
   out_4899541032027007789[2] = 0;
   out_4899541032027007789[3] = 0;
   out_4899541032027007789[4] = 0;
   out_4899541032027007789[5] = 0;
   out_4899541032027007789[6] = 1;
   out_4899541032027007789[7] = 0;
   out_4899541032027007789[8] = 0;
}
void h_24(double *state, double *unused, double *out_5328660616448437341) {
   out_5328660616448437341[0] = state[4];
   out_5328660616448437341[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4319137855613348602) {
   out_4319137855613348602[0] = 0;
   out_4319137855613348602[1] = 0;
   out_4319137855613348602[2] = 0;
   out_4319137855613348602[3] = 0;
   out_4319137855613348602[4] = 1;
   out_4319137855613348602[5] = 0;
   out_4319137855613348602[6] = 0;
   out_4319137855613348602[7] = 0;
   out_4319137855613348602[8] = 0;
   out_4319137855613348602[9] = 0;
   out_4319137855613348602[10] = 0;
   out_4319137855613348602[11] = 0;
   out_4319137855613348602[12] = 0;
   out_4319137855613348602[13] = 0;
   out_4319137855613348602[14] = 1;
   out_4319137855613348602[15] = 0;
   out_4319137855613348602[16] = 0;
   out_4319137855613348602[17] = 0;
}
void h_30(double *state, double *unused, double *out_6020570821464990184) {
   out_6020570821464990184[0] = state[4];
}
void H_30(double *state, double *unused, double *out_371844701899399591) {
   out_371844701899399591[0] = 0;
   out_371844701899399591[1] = 0;
   out_371844701899399591[2] = 0;
   out_371844701899399591[3] = 0;
   out_371844701899399591[4] = 1;
   out_371844701899399591[5] = 0;
   out_371844701899399591[6] = 0;
   out_371844701899399591[7] = 0;
   out_371844701899399591[8] = 0;
}
void h_26(double *state, double *unused, double *out_8624976142273687835) {
   out_8624976142273687835[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1158037713152951565) {
   out_1158037713152951565[0] = 0;
   out_1158037713152951565[1] = 0;
   out_1158037713152951565[2] = 0;
   out_1158037713152951565[3] = 0;
   out_1158037713152951565[4] = 0;
   out_1158037713152951565[5] = 0;
   out_1158037713152951565[6] = 0;
   out_1158037713152951565[7] = 1;
   out_1158037713152951565[8] = 0;
}
void h_27(double *state, double *unused, double *out_6550180944317446732) {
   out_6550180944317446732[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2595438773083342808) {
   out_2595438773083342808[0] = 0;
   out_2595438773083342808[1] = 0;
   out_2595438773083342808[2] = 0;
   out_2595438773083342808[3] = 1;
   out_2595438773083342808[4] = 0;
   out_2595438773083342808[5] = 0;
   out_2595438773083342808[6] = 0;
   out_2595438773083342808[7] = 0;
   out_2595438773083342808[8] = 0;
}
void h_29(double *state, double *unused, double *out_5077060968563327749) {
   out_5077060968563327749[0] = state[1];
}
void H_29(double *state, double *unused, double *out_882076046213791775) {
   out_882076046213791775[0] = 0;
   out_882076046213791775[1] = 1;
   out_882076046213791775[2] = 0;
   out_882076046213791775[3] = 0;
   out_882076046213791775[4] = 0;
   out_882076046213791775[5] = 0;
   out_882076046213791775[6] = 0;
   out_882076046213791775[7] = 0;
   out_882076046213791775[8] = 0;
}
void h_28(double *state, double *unused, double *out_907451073236489897) {
   out_907451073236489897[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4200322970855738799) {
   out_4200322970855738799[0] = 1;
   out_4200322970855738799[1] = 0;
   out_4200322970855738799[2] = 0;
   out_4200322970855738799[3] = 0;
   out_4200322970855738799[4] = 0;
   out_4200322970855738799[5] = 0;
   out_4200322970855738799[6] = 0;
   out_4200322970855738799[7] = 0;
   out_4200322970855738799[8] = 0;
}
void h_31(double *state, double *unused, double *out_9100903824215004755) {
   out_9100903824215004755[0] = state[8];
}
void H_31(double *state, double *unused, double *out_531829610919600089) {
   out_531829610919600089[0] = 0;
   out_531829610919600089[1] = 0;
   out_531829610919600089[2] = 0;
   out_531829610919600089[3] = 0;
   out_531829610919600089[4] = 0;
   out_531829610919600089[5] = 0;
   out_531829610919600089[6] = 0;
   out_531829610919600089[7] = 0;
   out_531829610919600089[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1099665464184721179) {
  err_fun(nom_x, delta_x, out_1099665464184721179);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4420002132005042565) {
  inv_err_fun(nom_x, true_x, out_4420002132005042565);
}
void car_H_mod_fun(double *state, double *out_6269193584076680151) {
  H_mod_fun(state, out_6269193584076680151);
}
void car_f_fun(double *state, double dt, double *out_1825805570165161384) {
  f_fun(state,  dt, out_1825805570165161384);
}
void car_F_fun(double *state, double dt, double *out_4195817935556502074) {
  F_fun(state,  dt, out_4195817935556502074);
}
void car_h_25(double *state, double *unused, double *out_7471202214093873351) {
  h_25(state, unused, out_7471202214093873351);
}
void car_H_25(double *state, double *unused, double *out_4899541032027007789) {
  H_25(state, unused, out_4899541032027007789);
}
void car_h_24(double *state, double *unused, double *out_5328660616448437341) {
  h_24(state, unused, out_5328660616448437341);
}
void car_H_24(double *state, double *unused, double *out_4319137855613348602) {
  H_24(state, unused, out_4319137855613348602);
}
void car_h_30(double *state, double *unused, double *out_6020570821464990184) {
  h_30(state, unused, out_6020570821464990184);
}
void car_H_30(double *state, double *unused, double *out_371844701899399591) {
  H_30(state, unused, out_371844701899399591);
}
void car_h_26(double *state, double *unused, double *out_8624976142273687835) {
  h_26(state, unused, out_8624976142273687835);
}
void car_H_26(double *state, double *unused, double *out_1158037713152951565) {
  H_26(state, unused, out_1158037713152951565);
}
void car_h_27(double *state, double *unused, double *out_6550180944317446732) {
  h_27(state, unused, out_6550180944317446732);
}
void car_H_27(double *state, double *unused, double *out_2595438773083342808) {
  H_27(state, unused, out_2595438773083342808);
}
void car_h_29(double *state, double *unused, double *out_5077060968563327749) {
  h_29(state, unused, out_5077060968563327749);
}
void car_H_29(double *state, double *unused, double *out_882076046213791775) {
  H_29(state, unused, out_882076046213791775);
}
void car_h_28(double *state, double *unused, double *out_907451073236489897) {
  h_28(state, unused, out_907451073236489897);
}
void car_H_28(double *state, double *unused, double *out_4200322970855738799) {
  H_28(state, unused, out_4200322970855738799);
}
void car_h_31(double *state, double *unused, double *out_9100903824215004755) {
  h_31(state, unused, out_9100903824215004755);
}
void car_H_31(double *state, double *unused, double *out_531829610919600089) {
  H_31(state, unused, out_531829610919600089);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
