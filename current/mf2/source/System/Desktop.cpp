#include "Desktop.h"
#include <string.h>
#include "Value.h"

namespace mf2 {

Desktop desktop;

void Desktop::init() {
    IwGxInit();
    IwGxLightingOff();
    width = IwGxGetScreenWidth();
    height = IwGxGetScreenHeight();
	IwGxSetColClear(0, 0, 0, 0);
	duration = 1000 / 60;
	v_width = v_height = 0;
}

void Desktop::release() {
    IwGxTerminate();
}

void Desktop::update() {
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
}

void Desktop::refresh() {
    IwGxFlush();
    IwGxSwapBuffers();
    s3eDeviceYield(duration);   
}

bool Desktop::setValue(const char* name, const char* value) {
	if (strcmp(name, WIDTH_PROPERTY) == 0) {
		v_width = Value::strToNum(value);
		return true;
	}
	if (strcmp(name, HEIGHT_PROPERTY) == 0) {
		v_height = Value::strToNum(value);
		return true;
	}
	if (strcmp(name, ORIENTATION_PROPERTY) == 0) {
		if (strcmp(value, PORTRAIT_ORIENTATION) == 0) {
			s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_PORTRAIT_FIXED); 
			return true;
		}
		if (strcmp(value, LANDSCAPE_ORIENTATION) == 0) {
			s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_LANDSCAPE); 
			return true;
		}
		return true;
	}
	return false;
}

int Desktop::getXSize(int x) const {
	if (v_width != 0) {
		return (x * width) / v_width;
	}
	if (v_height != 0) {
		return (x * height) / v_height;
	}
	return x;
}

int Desktop::getYSize(int y) const {
	if (v_height != 0) {
		return (y * height) / v_height;
	}
	if (v_width != 0) {
		return (y * width) / v_width;
	}
	return y;
}

}