#pragma once

class HtmlWindow 
	: public htmlayout::event_handler
	, public htmlayout::notification_handler<HtmlWindow>
{
public:
	static HINSTANCE s_hinstance;
	static HWND s_hwnd;
public:
	HWND hwnd;
	std::wstring m_title;
	htmlayout::dom::element body;
	htmlayout::dom::element caption;
	htmlayout::dom::element button_min;
	htmlayout::dom::element button_max;
	htmlayout::dom::element button_icon;
	htmlayout::dom::element button_close;
	htmlayout::dom::element corner;
	virtual void Create(const wchar_t * filename, int x, int y, int width, int height, const wchar_t * caption = 0);
	static HtmlWindow * Self(HWND hWnd);
	static ATOM RegisterClass(HINSTANCE hInstance);
    LRESULT on_load_data(LPNMHL_LOAD_DATA pnmld);
	LRESULT on_document_complete();
	void DoModal(int cmd);
protected:
	HtmlWindow();
	int HitTest(int x, int y);
	HELEMENT GetRoot();
	bool IsWindowMinimized() const;
	bool IsWindowMaximized() const;
	virtual BOOL on_event(HELEMENT he, HELEMENT target, BEHAVIOR_EVENTS type, UINT_PTR reason);
	static void Self(HWND hWnd, HtmlWindow * inst);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual int OnMessage(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnShow() = 0;
	virtual void OnDocumentComplete() = 0;
	bool LoadResourceData(LPCWSTR uri, PBYTE& pb, DWORD& cb);
	void ModalLoop();
private:
	bool m_modal;
};
