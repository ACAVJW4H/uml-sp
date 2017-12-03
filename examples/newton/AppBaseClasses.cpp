/******************************************************
 * File:         AppBaseClasses.cpp
 * Author:       Vasily I.Gurianov
 * Create date:  2017-11-21
 * Testing:      CodeGear C++Builder 2007
 *
 * �lassical mechanics
 *
 * Define methods
 *
  * ***************************************************/

//---------------------------------------------------------------------------

#pragma hdrstop

#include "AppBaseClasses.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//void PhysicalSpace::shift_space(int n) {
// ����� ������������ �� ������ n
//ShowMessage( "0 � "+IntToStr(headOfList->x));
//}
//void Composite::inversion_space(int) {

//}
Carrier::Carrier(Jump *j) {direction = j->direction;}

Jump Carrier::createJump() {Jump p; p.direction = this->direction; return p;}


ObserverX::ObserverX(Subject *s) {
	this->_subject = s;
	iTime = 0; x = 0; v = 0; a = 0; x2=0;
}
void ObserverX::Update(Subject *cs) {
	//if (_subject == cs) {
	this->iTime = cs->iTime;
	this->x = cs->x;
	this->v = cs->v;
	this->a = cs->a;
	this->x2 = cs->x2;
	this->imp = cs->imp;
	this->kinetic_energy = cs->kinetic_energy;
	this->potential_energy = cs->potential_energy;
	this->name_sk = cs->Caption;
	this->CreateDetect = cs->CreateDetect;
	this->DestroyDetect = cs->DestroyDetect;
	//ShowMessage( "� === "+IntToStr(x));
	// }
}
ObserverV::ObserverV(Subject *s) {
	this->_subject = s;
	x = -2; v = -2;
}
void ObserverV::Update(Subject *cs) {
	//if (_subject == cs) {
	this->v = cs->v;
	ShowMessage( "v === "+IntToStr(v));
	//
}

TreeLeaf::TreeLeaf() { // ������� � ��.������
	headItemOfJump = NULL; currentItemOfJump = NULL;
	headItemOfSkip = NULL; // m=1
	currentItemOfSkip = headItemOfSkip;
	isActive = false; hasStableState = true;
	};
TreeLeaf::TreeLeaf(int mm) {
	//����� ������ ���������� � ������������
		headItemOfJump = NULL; currentItemOfJump = headItemOfJump; headItemOfSkip = NULL;
	// ����� = ����� ������ + 1
	// mm = 0 �� ����� ����
	if (mm < 1) ShowMessage( "mm <1; mm= "+IntToStr(mm));
	int m = mm - 1;
	for (int i = 0; i < m; i++) {
	if (i==0) {headItemOfSkip = new Skip; currentItemOfSkip = headItemOfSkip;}
	else {currentItemOfSkip->next = new Skip;	currentItemOfSkip=currentItemOfSkip->next;};
	};
	currentItemOfSkip = headItemOfSkip;
	isActive = false; hasStableState = true;
	};

// ---------------------------------------
// �������� ������
void AbstractTreeNode::move() {
Temp *temp, *tm;
temp = new Temp;
tm = temp;

ListItem *b; b = headOfList;
while (b->left != NULL) b = b->left;  //� ������
while (b->right != NULL) {tm->next = new Temp; tm=tm->next;
b = b->right;}


int ii=0;
do {
ii++; // ������� ������
// �������������� ��� ������
this->reviveCells();

b = headOfList;
while (b->left != NULL) b = b->left;  //� ������

do {
	if (!b->isDisable) { // ������ �� ����������
		if (b->something != NULL) { // ���� �������
			Component *p; p = b->something;
			//ShowMessage( IntToStr(ii)+"->� = "+IntToStr(b->x));
			if (p->isActive) { // ������� �������
			//ShowMessage( "���. � � = "+IntToStr(b->x));
				p = this->replace(b,p); // ���������� �������
				//if (p->number == 6 ) {ShowMessage("ex "+frame->Caption); };
				p->Run();  // ���� �� ���������, �� ������������ p ; ����� ��� ? � something - �����, ������ �� ���� �� ��������
				//if (b->right != NULL) b->right->isDisable = true; // ������ left ������ ����������
			};
		};

	b->isDisable = true;  // �������� ������ ��� ������������
	};
b = b->right;
} while (b != NULL);

temp = temp->next;
} while (temp != NULL); // end for
//ShowMessage( "ii = "+IntToStr(ii));
}; // end void move()


// -----------------------------------------------------------
Component * AbstractTreeNode::replace(ListItem *b, Component *p) {
// ���������� �������, ����� ������� �� �������������
//Component pp = b->get();
if (p->currentItemOfJump != NULL) {
if (p->currentItemOfJump->direction == FORWARD) {
	if (b->right != NULL) {
		//if (!b->something->isStable) {b->something = p->getA(); b->right->something = p->getB();
		//} else {
		if (b->right->something != NULL) {bump(b);this->CreateDetect = frame->Caption;
 };//bump(p);
		b->right->something = p; b->something = NULL;
		b->right->isDisable = true;
		//};
	};
};
if (p->currentItemOfJump->direction == BACKWARD) {
	if (b->left != NULL) {
		//if (!b->something->isStable) {b->left->something = p->getA(); b->something = p->getB();
		//} else {
		if (b->left->something != NULL) {bump(b); this->CreateDetect = frame->Caption;
p = b->something;
		b->left->something = p; b->something = NULL;
		//ShowMessage( "pp = "+IntToStr(b->left->something->number));
		}; // ���� ���� �� ���������
		b->left->something = p; b->something = NULL;

		//};
	};
};
} else { if (!b->something->hasStableState) {
			b->something = p->getA(); b->right->something = p->getB();
			this->DestroyDetect = frame->Caption;
			b->right->isDisable = true;
			ShowMessage( "r->� = "+IntToStr(b->x));
			};
}; //if (p->currentItemOfJump != NULL)
return p;
}; // end replace

void AbstractTreeNode::clearOfSkip() {
Skip *m;
do { m = headItemOfSkip;
headItemOfSkip = headItemOfSkip->next;
delete m;
} while (headItemOfSkip != NULL);
};
void AbstractTreeNode::addOfSkip(Component *s) {
Skip *m = s->headItemOfSkip; Skip *n;
while (m != NULL ) {
	n = new Skip; n->next = headItemOfSkip; headItemOfSkip = n;
	m = m->next;
};
};

void AbstractTreeNode::reviveCells() { // �������� ������
ListItem *previous; ListItem *b;
// �������������� ��� ������
b = headOfList;
do { b->isDisable = false;
previous = b; b = b->right;
} while (b != NULL);
b = previous;
do { b->isDisable = false;
b = b->left;
} while (b != NULL);
}; // void reviveCells()

// ��������������� ������� �������
void AbstractTreeNode::actuate() {
	for (int i = 0; i < 1000; i++) {
	if (this->m[i] != NULL) {
		if (m[i]->something != NULL) m[i]->something->actuate() ;
	};
	};
	if (headItemOfJump != NULL) {isActive = true; };
	currentItemOfJump = headItemOfJump;
};


