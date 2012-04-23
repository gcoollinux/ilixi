/*
 * ImageDialog.cpp
 *
 *  Created on: 10 Nov 2011
 *      Author: tarik
 */

#include "ImageDialog.h"
#include "ui/VBoxLayout.h"
#include "ui/HBoxLayout.h"
#include "ui/Icon.h"
#include "ui/ScrollArea.h"
#include "ui/PushButton.h"
#include "ui/ToolButton.h"
#include "ui/CheckBox.h"

using namespace ilixi;

ImageDialog::ImageDialog(const std::string& title, Widget* parent) :
    Dialog(title, OKButtonOption, parent)
{
  setLayout(new HBoxLayout());

  VBoxLayout* vb1 = new VBoxLayout();
  _icon = new Icon();
  _icon->setMinimumSize(196, 196);
  _icon->setConstraints(FixedConstraint, FixedConstraint);
  vb1->addWidget(_icon);

  PushButton* pb1 = new PushButton("PushButton 1");
  vb1->addWidget(pb1);

  PushButton* pb2 = new PushButton("PushButton 2");
  vb1->addWidget(pb2);

  PushButton* pb3 = new PushButton("PushButton 3");
  vb1->addWidget(pb3);

  PushButton* pb4 = new PushButton("PushButton 4");
  vb1->addWidget(pb4);

  PushButton* pb5 = new PushButton("PushButton 5");
  vb1->addWidget(pb5);
  addWidget(vb1);

  VBoxLayout* vb2 = new VBoxLayout();
  PushButton* pb6 = new PushButton("PushButton 6");
  vb2->addWidget(pb6);

  PushButton* pb7 = new PushButton("PushButton 7");
  vb2->addWidget(pb7);

  PushButton* pb8 = new PushButton("PushButton 8");
  vb2->addWidget(pb8);

  PushButton* pb9 = new PushButton("PushButton 9");
  vb2->addWidget(pb9);

  PushButton* pb10 = new PushButton("PushButton 10");
  vb2->addWidget(pb10);
  addWidget(vb2);

  VBoxLayout* vb3 = new VBoxLayout();
  PushButton* pb11 = new PushButton("PushButton 11");
  vb3->addWidget(pb11);

  PushButton* pb12 = new PushButton("PushButton 12");
  vb3->addWidget(pb12);

  PushButton* pb13 = new PushButton("PushButton 13");
  vb3->addWidget(pb13);

  PushButton* pb14 = new PushButton("PushButton 14");
  vb3->addWidget(pb14);

  CheckBox* pb15 = new CheckBox("CheckBox 15");
  vb3->addWidget(pb15);
  addWidget(vb3);
}

ImageDialog::~ImageDialog()
{
}

void
ImageDialog::setImagePath(const std::string& path)
{
  _icon->setDefaultImage(path);
}
