
#include "fix16.h"

const fix16_t fix16_cos_table[360] = {
	256, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248,
	247, 246, 244, 243, 242, 240, 238, 237, 235, 233, 232, 230, 228, 226, 223,
	221, 219, 217, 214, 212, 209, 207, 204, 201, 198, 196, 193, 190, 187, 184,
	181, 177, 174, 171, 167, 164, 161, 157, 154, 150, 146, 143, 139, 135, 131,
	127, 124, 120, 116, 112, 108, 104, 100, 95, 91, 87, 83, 79, 74, 70, 66, 61,
	57, 53, 48, 44, 40, 35, 31, 26, 22, 17, 13, 8, 4, 0, -4, -8, -13, -17, -22,
	-26, -31, -35, -40, -44, -48, -53, -57, -61, -66, -70, -74, -79, -83, -87,
	-91, -95, -100, -104, -108, -112, -116, -120, -124, -128, -131, -135, -139,
	-143, -146, -150, -154, -157, -161, -164, -167, -171, -174, -177, -181, -184,
	-187, -190, -193, -196, -198, -201, -204, -207, -209, -212, -214, -217, -219,
	-221, -223, -226, -228, -230, -232, -233, -235, -237, -238, -240, -242, -243,
	-244, -246, -247, -248, -249, -250, -251, -252, -252, -253, -254, -254, -255,
	-255, -255, -255, -255, -256, -255, -255, -255, -255, -255, -254, -254, -253,
	-252, -252, -251, -250, -249, -248, -247, -246, -244, -243, -242, -240, -238,
	-237, -235, -233, -232, -230, -228, -226, -223, -221, -219, -217, -214, -212,
	-209, -207, -204, -201, -198, -196, -193, -190, -187, -184, -181, -177, -174,
	-171, -167, -164, -161, -157, -154, -150, -146, -143, -139, -135, -131, -127,
	-124, -120, -116, -112, -108, -104, -100, -95, -91, -87, -83, -79, -74, -70,
	-66, -61, -57, -53, -48, -44, -40, -35, -31, -26, -22, -17, -13, -8, -4, 0,
	4, 8, 13, 17, 22, 26, 31, 35, 40, 44, 48, 53, 57, 61, 66, 70, 74, 79, 83,
	87, 91, 95, 100, 104, 108, 112, 116, 120, 124, 127, 131, 135, 139, 143, 146,
	150, 154, 157, 161, 164, 167, 171, 174, 177, 181, 184, 187, 190, 193, 196,
	198, 201, 204, 207, 209, 212, 214, 217, 219, 221, 223, 226, 228, 230, 232,
	233, 235, 237, 238, 240, 242, 243, 244, 246, 247, 248, 249, 250, 251, 252,
	252, 253, 254, 254, 255, 255, 255, 255, 255
};

const fix16_t fix16_sin_table[360] = {
	0, 4, 8, 13, 17, 22, 26, 31, 35, 40, 44, 48, 53, 57, 61, 66, 70, 74, 79, 83,
	87, 91, 95, 100, 104, 108, 112, 116, 120, 124, 128, 131, 135, 139, 143, 146,
	150, 154, 157, 161, 164, 167, 171, 174, 177, 181, 184, 187, 190, 193, 196,
	198, 201, 204, 207, 209, 212, 214, 217, 219, 221, 223, 226, 228, 230, 232,
	233, 235, 237, 238, 240, 242, 243, 244, 246, 247, 248, 249, 250, 251, 252,
	252, 253, 254, 254, 255, 255, 255, 255, 255, 256, 255, 255, 255, 255, 255,
	254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 244, 243, 242, 240,
	238, 237, 235, 233, 232, 230, 228, 226, 223, 221, 219, 217, 214, 212, 209,
	207, 204, 201, 198, 196, 193, 190, 187, 184, 181, 177, 174, 171, 167, 164,
	161, 157, 154, 150, 146, 143, 139, 135, 131, 128, 124, 120, 116, 112, 108,
	104, 100, 95, 91, 87, 83, 79, 74, 70, 66, 61, 57, 53, 48, 44, 40, 35, 31,
	26, 22, 17, 13, 8, 4, 0, -4, -8, -13, -17, -22, -26, -31, -35, -40, -44,
	-48, -53, -57, -61, -66, -70, -74, -79, -83, -87, -91, -95, -100, -104,
	-108, -112, -116, -120, -124, -128, -131, -135, -139, -143, -146, -150,
	-154, -157, -161, -164, -167, -171, -174, -177, -181, -184, -187, -190,
	-193, -196, -198, -201, -204, -207, -209, -212, -214, -217, -219, -221,
	-223, -226, -228, -230, -232, -233, -235, -237, -238, -240, -242, -243,
	-244, -246, -247, -248, -249, -250, -251, -252, -252, -253, -254, -254,
	-255, -255, -255, -255, -255, -256, -255, -255, -255, -255, -255, -254,
	-254, -253, -252, -252, -251, -250, -249, -248, -247, -246, -244, -243,
	-242, -240, -238, -237, -235, -233, -232, -230, -228, -226, -223, -221,
	-219, -217, -214, -212, -209, -207, -204, -201, -198, -196, -193, -190,
	-187, -184, -181, -177, -174, -171, -167, -164, -161, -157, -154, -150,
	-146, -143, -139, -135, -131, -128, -124, -120, -116, -112, -108, -104,
	-100, -95, -91, -87, -83, -79, -74, -70, -66, -61, -57, -53, -48, -44,
	-40, -35, -31, -26, -22, -17, -13, -8, -4
};
