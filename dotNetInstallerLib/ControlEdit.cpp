#include "StdAfx.h"
#include "XmlAttribute.h"
#include "ControlEdit.h"
#include "InstallerSession.h"
#include "InstallerLog.h"

ControlEdit::ControlEdit()
	: ControlText(control_type_edit)
{

}

void ControlEdit::Load(TiXmlElement * node)
{
	id = node->Attribute("id");
	ControlText::Load(node);
}

std::wstring ControlEdit::GetString() const
{
	std::wstringstream ss;
	ss << L"'edit' control, id=" << id << L", " << ControlText::GetString();
	return ss.str();
}
