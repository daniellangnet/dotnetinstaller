#pragma once
#include "ControlText.h"

class ControlHyperlink : public ControlText
{
public:
    ControlHyperlink();
public:
	XmlAttribute uri;
	void Load(TiXmlElement * node);
	std::wstring GetString() const;
};

typedef shared_any<ControlHyperlink *, close_delete> ControlHyperlinkPtr;
