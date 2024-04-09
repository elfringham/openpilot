#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_1099665464184721179);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4420002132005042565);
void car_H_mod_fun(double *state, double *out_6269193584076680151);
void car_f_fun(double *state, double dt, double *out_1825805570165161384);
void car_F_fun(double *state, double dt, double *out_4195817935556502074);
void car_h_25(double *state, double *unused, double *out_7471202214093873351);
void car_H_25(double *state, double *unused, double *out_4899541032027007789);
void car_h_24(double *state, double *unused, double *out_5328660616448437341);
void car_H_24(double *state, double *unused, double *out_4319137855613348602);
void car_h_30(double *state, double *unused, double *out_6020570821464990184);
void car_H_30(double *state, double *unused, double *out_371844701899399591);
void car_h_26(double *state, double *unused, double *out_8624976142273687835);
void car_H_26(double *state, double *unused, double *out_1158037713152951565);
void car_h_27(double *state, double *unused, double *out_6550180944317446732);
void car_H_27(double *state, double *unused, double *out_2595438773083342808);
void car_h_29(double *state, double *unused, double *out_5077060968563327749);
void car_H_29(double *state, double *unused, double *out_882076046213791775);
void car_h_28(double *state, double *unused, double *out_907451073236489897);
void car_H_28(double *state, double *unused, double *out_4200322970855738799);
void car_h_31(double *state, double *unused, double *out_9100903824215004755);
void car_H_31(double *state, double *unused, double *out_531829610919600089);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}