/*
 * CCommon.h
 *
 *  Created on: 2017/01/09
 *      Author: kyon
 */

#ifndef GUI_CCOMMON_H_
#define GUI_CCOMMON_H_

#define INIT_TOOL_BMP(bmp) \
    toolBarBitmaps[Tool_##bmp] = wxBitmap(bmp##_xpm)


namespace NesEngine {

class CCommon {
public:
	CCommon();
	virtual ~CCommon();
	static const CCommon* getInstance()
	{
		if (CCommon::instance == nullptr) {
			CCommon::instance = new CCommon();
		}
		return CCommon::instance;
	}

private:
	static CCommon* instance;

};

} /* namespace NesEngine */

#endif /* GUI_CCOMMON_H_ */
