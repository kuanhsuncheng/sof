// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2021 Intel Corporation. All rights reserved.
//
// Author: Shriram Shastry <malladi.sastry@linux.intel.com>
//

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <math.h>
#include <cmocka.h>

#include <sof/audio/format.h>
#include <sof/math/trig.h>
/* 'Error (max = 0.000061), THD+N  = -91.518584' */
#define CMP_TOLERANCE	0.000065
#define _M_PI		3.14159265358979323846	/* pi */
/* Reference table generated by cos(), gcc-4.3.2 */
static const float cos_ref_table[] = {
	1.000000000000000, 0.999847695156391, 0.999390827019096, 0.998629534754574,
	0.997564050259824, 0.996194698091746, 0.994521895368273, 0.992546151641322,
	0.99026806874157, 0.987688340595138, 0.984807753012208, 0.981627183447664,
	0.978147600733806, 0.974370064785235, 0.970295726275996, 0.965925826289068,
	0.961261695938319, 0.956304755963035, 0.951056516295154, 0.945518575599317,
	0.939692620785908, 0.933580426497202, 0.927183854566787, 0.92050485345244,
	0.913545457642601, 0.90630778703665, 0.898794046299167, 0.891006524188368,
	0.882947592858927, 0.874619707139396, 0.866025403784439, 0.857167300702112,
	0.848048096156426, 0.838670567945424, 0.829037572555042, 0.819152044288992,
	0.809016994374947, 0.798635510047293, 0.788010753606722, 0.777145961456971,
	0.766044443118978, 0.754709580222772, 0.743144825477394, 0.731353701619171,
	0.719339800338651, 0.707106781186548, 0.694658370458997, 0.681998360062498,
	0.669130606358858, 0.656059028990507, 0.642787609686539, 0.629320391049838,
	0.615661475325658, 0.601815023152048, 0.587785252292473, 0.573576436351046,
	0.559192903470747, 0.544639035015027, 0.529919264233205, 0.515038074910054,
	0.500000000000000, 0.484809620246337, 0.469471562785891, 0.453990499739547,
	0.438371146789077,  0.422618261740699, 0.4067366430758, 0.390731128489274,
	0.374606593415912, 0.3583679495453, 0.342020143325669, 0.325568154457157,
	0.309016994374947, 0.292371704722737, 0.275637355816999, 0.258819045102521,
	0.241921895599668, 0.224951054343865, 0.207911690817759, 0.190808995376545,
	0.17364817766693, 0.156434465040231, 0.139173100960066, 0.121869343405147,
	0.104528463267653, 0.0871557427476581, 0.0697564737441255, 0.052335956242944,
	0.0348994967025011, 0.0174524064372834, 6.12323399573677e-17, -0.0174524064372835,
	-0.0348994967025007, -0.0523359562429436, -0.0697564737441253, -0.0871557427476582,
	-0.104528463267653, -0.121869343405147, -0.139173100960065, -0.156434465040231,
	-0.17364817766693, -0.190808995376545, -0.207911690817759, -0.224951054343865,
	-0.241921895599668, -0.258819045102521, -0.275637355816999, -0.292371704722737,
	-0.309016994374947, -0.325568154457156, -0.342020143325669, -0.3583679495453,
	-0.374606593415912, -0.390731128489274, -0.4067366430758, -0.422618261740699,
	-0.438371146789078, -0.453990499739547, -0.469471562785891, -0.484809620246337,
	-0.500000000000000, -0.515038074910054, -0.529919264233205, -0.544639035015027,
	-0.559192903470747, -0.573576436351046, -0.587785252292473, -0.601815023152048,
	-0.615661475325658, -0.629320391049837, -0.642787609686539, -0.656059028990507,
	-0.669130606358858, -0.681998360062498, -0.694658370458997, -0.707106781186547,
	-0.719339800338651, -0.73135370161917, -0.743144825477394, -0.754709580222772,
	-0.766044443118978, -0.777145961456971, -0.788010753606722, -0.798635510047293,
	-0.809016994374947, -0.819152044288992, -0.829037572555042, -0.838670567945424,
	-0.848048096156426, -0.857167300702112, -0.866025403784439, -0.874619707139396,
	-0.882947592858927, -0.891006524188368, -0.898794046299167, -0.90630778703665,
	-0.913545457642601, -0.92050485345244, -0.927183854566787, -0.933580426497202,
	-0.939692620785908, -0.945518575599317, -0.951056516295154, -0.956304755963035,
	-0.961261695938319, -0.965925826289068, -0.970295726275996, -0.974370064785235,
	-0.978147600733806, -0.981627183447664, -0.984807753012208, -0.987688340595138,
	-0.99026806874157, -0.992546151641322, -0.994521895368273, -0.996194698091746,
	-0.997564050259824, -0.998629534754574, -0.999390827019096, -0.999847695156391,
	-1.000000000000000, -0.999847695156391, -0.999390827019096, -0.998629534754574,
	-0.997564050259824, -0.996194698091746, -0.994521895368273, -0.992546151641322,
	-0.99026806874157, -0.987688340595138, -0.984807753012208, -0.981627183447664,
	-0.978147600733806, -0.974370064785235, -0.970295726275997, -0.965925826289068,
	-0.961261695938319, -0.956304755963036, -0.951056516295154, -0.945518575599317,
	-0.939692620785908, -0.933580426497202, -0.927183854566787, -0.92050485345244,
	-0.913545457642601, -0.90630778703665, -0.898794046299167, -0.891006524188368,
	-0.882947592858927, -0.874619707139396, -0.866025403784439, -0.857167300702112,
	-0.848048096156426, -0.838670567945424, -0.829037572555042, -0.819152044288992,
	-0.809016994374947, -0.798635510047293, -0.788010753606722, -0.777145961456971,
	-0.766044443118978, -0.754709580222772, -0.743144825477394, -0.731353701619171,
	-0.719339800338651, -0.707106781186548, -0.694658370458997, -0.681998360062499,
	-0.669130606358858, -0.656059028990508, -0.642787609686539, -0.629320391049837,
	-0.615661475325658, -0.601815023152048, -0.587785252292473, -0.573576436351046,
	-0.559192903470747, -0.544639035015027, -0.529919264233205, -0.515038074910054,
	-0.500000000000000, -0.484809620246337, -0.469471562785891, -0.453990499739547,
	-0.438371146789078, -0.4226182617407, -0.4067366430758, -0.390731128489274,
	-0.374606593415912, -0.358367949545301, -0.342020143325669, -0.325568154457157,
	-0.309016994374948, -0.292371704722737, -0.275637355816999, -0.258819045102521,
	-0.241921895599668, -0.224951054343865, -0.20791169081776, -0.190808995376545,
	-0.17364817766693,  -0.156434465040231, -0.139173100960065, -0.121869343405147,
	-0.104528463267653, -0.0871557427476582, -0.0697564737441256, -0.0523359562429443,
	-0.0348994967025016, -0.0174524064372835, -1.83697019872103e-16, 0.0174524064372831,
	0.0348994967025013, 0.0523359562429439, 0.0697564737441252, 0.0871557427476579,
	0.104528463267653, 0.121869343405148, 0.139173100960065, 0.156434465040231,
	0.17364817766693, 0.190808995376544, 0.207911690817759, 0.224951054343865,
	0.241921895599667, 0.258819045102521, 0.275637355816999, 0.292371704722737,
	0.309016994374947, 0.325568154457156, 0.342020143325668, 0.3583679495453,
	0.374606593415912, 0.390731128489273, 0.406736643075801, 0.4226182617407,
	0.438371146789077, 0.453990499739547, 0.46947156278589,  0.484809620246337,
	0.500000000000000, 0.515038074910054, 0.529919264233205, 0.544639035015027,
	0.559192903470746, 0.573576436351046, 0.587785252292473, 0.601815023152048,
	0.615661475325659, 0.629320391049838, 0.642787609686539, 0.656059028990507,
	0.669130606358858, 0.681998360062498, 0.694658370458997, 0.707106781186547,
	0.719339800338651, 0.731353701619171, 0.743144825477394, 0.754709580222772,
	0.766044443118978, 0.777145961456971, 0.788010753606722, 0.798635510047293,
	0.809016994374947, 0.819152044288992, 0.829037572555041, 0.838670567945424,
	0.848048096156425, 0.857167300702112, 0.866025403784438, 0.874619707139396,
	0.882947592858927, 0.891006524188368, 0.898794046299167, 0.90630778703665,
	0.913545457642601, 0.92050485345244, 0.927183854566787, 0.933580426497202,
	0.939692620785908, 0.945518575599317, 0.951056516295154, 0.956304755963036,
	0.961261695938319, 0.965925826289068, 0.970295726275996, 0.974370064785235,
	0.978147600733806, 0.981627183447664, 0.984807753012208, 0.987688340595138,
	0.99026806874157, 0.992546151641322, 0.994521895368273, 0.996194698091746,
	0.997564050259824, 0.998629534754574, 0.999390827019096, 0.999847695156391,
	1
};

static void test_math_trig_cos_fixed(void **state)
{
	(void)state;
	int theta;

	for (theta = 0; theta < 360; ++theta) {
		double rad = _M_PI * (theta / 180.0);
		int32_t rad_q28 = Q_CONVERT_FLOAT(rad, 28);

		float r = Q_CONVERT_QTOF(cos_fixed_16b(rad_q28), 15);
		float diff = fabsf(cos_ref_table[theta] - r);

		if (diff > CMP_TOLERANCE) {
			printf("%s: diff for %d deg = %.10f\n", __func__,
			       theta, diff);
		}

		assert_true(diff <= CMP_TOLERANCE);
	}
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_math_trig_cos_fixed)
	};

	cmocka_set_message_output(CM_OUTPUT_TAP);

	return cmocka_run_group_tests(tests, NULL, NULL);
}
