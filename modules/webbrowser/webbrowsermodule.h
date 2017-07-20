/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2017                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __OPENSPACE_MODULE_WEBBROWSER___WEBBROWSERMODULE___H__
#define __OPENSPACE_MODULE_WEBBROWSER___WEBBROWSERMODULE___H__

#include <openspace/util/openspacemodule.h>
#include <ghoul/filesystem/directory.h>
#include <include/openspace/engine/configurationmanager.h>
#include <include/wrapper/cef_helpers.h>
#include <include/cef_browser.h>
#include <modules/webbrowser/include/eventhandler.h>

namespace openspace {

#ifdef WIN32
static const std::string SUBPROCESS_ENDING = ".exe";
#else
static const std::string SUBPROCESS_ENDING = "";
#endif

class WebBrowserModule : public OpenSpaceModule {
public:
    static constexpr const char* Name = "WebBrowser";
    WebBrowserModule();
    ~WebBrowserModule();
    void internalInitialize();

    int addBrowser(CefBrowser*);
    void removeBrowser(CefBrowser*);

    void attachEventHandler(std::shared_ptr<BrowserInstance> browserInstance);

private:
	void attachDebugSettings(CefSettings&);
    std::vector<CefRefPtr<CefBrowser>> browsers;
    std::string findHelperExecutable();
    EventHandler eventHandler;
};

} // namespace openspace

#endif // __OPENSPACE_MODULE_WEBBROWSER___WEBBROWSERMODULE___H__