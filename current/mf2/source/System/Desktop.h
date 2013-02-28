#ifndef _DESKTOP_H_
#define _DESKTOP_H_

#include "IwGx.h"
#include "AbstractConfigurable.h"

#define WIDTH_PROPERTY        "width"
#define HEIGHT_PROPERTY       "height"
#define ORIENTATION_PROPERTY  "orientation"

#define PORTRAIT_ORIENTATION  "portrait"
#define LANDSCAPE_ORIENTATION "landscape"

namespace mf2 {

class Desktop: public AbstractConfigurable {
	private:
		int  width,  v_width;
		int  height, v_height;
		int  duration;
	public:
		void init();
		void release();
        void update();
        void refresh();
        int  getWidth()  const {return width;}
        int  getHeight() const {return height;}
		int  getXSize(int x) const;
		int  getYSize(int y) const;

		virtual bool setValue(const char* name, const char* value);
};

extern Desktop desktop;

}

#endif	// _DESKTOP_H_
