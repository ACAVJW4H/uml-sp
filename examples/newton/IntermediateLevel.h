/******************************************************
 * File:         IntermediateLevel.h
 * Author:       Vasily I.Gurianov
 * Create date:  2017-11-21
 * Testing:      CodeGear C++Builder 2007
 *
 * �lassical mechanics
 *
 *  IntermediateLevel:
 *     class SpecialTreeNode
 *
 *     class OrdinaryTreeNode
 *
 * ***************************************************/

 //---------------------------------------------------------------------------

#ifndef IntermediateLevelH
#define IntermediateLevelH

#include "AppBaseClasses.h"

// ============== ������ �������������� ���� =========================

// ������������ �������� ����� �������
// ���� �� ���� ������ ����� ����������� �����
class SpecialTreeNode: public AbstractTreeNode {
public:

	SpecialTreeNode() {

int r = 990;
this->buildSpace(r);

TreeLeaf *p;
// ��������� �������
p = new TreeLeaf;
p->headItemOfSkip = new Skip;
p->headItemOfSkip->next = p->headItemOfSkip; // ����������� �����
p->currentItemOfSkip = p->headItemOfSkip;
p->number = 0;
p->headItemOfJump = NULL; p->currentItemOfJump = p->headItemOfJump;
this->headOfList->left->something = p;   // � ����� ��������� ������; ����� ���� ������������

// ����� �������
//headItemOfJump = new Jump; //headItemOfJump->direction = FORWARD;
currentItemOfJump = headItemOfJump;
//headItemOfSkip = headOfList->something->headItemOfSkip;
headItemOfSkip = new Skip; //headItemOfSkip->next = new Skip;
headItemOfSkip->next = headItemOfSkip; // ���� ����������� �����
currentItemOfSkip = headItemOfSkip;
this->hasStableState = true;
this->isActive = false;

// ������� �������
frame = new ConcreteSubject(headOfList,0,"K0");
this->eProbe = new ObserverX(frame);
frame->observerX = eProbe;
} // SpecialTreeNode()
// ----------------------------------
	// ����� ������������� �������
	Skip *getListOfSkip() {  // ���������� �������
	// ������ ������ � ���������� ������
	return headItemOfSkip;
	}

};  // SpecialTreeNode class
// --------------------- /


// ============== ������ �������������� ���� =========================
// ������������ �������� ���� ������
// ����� ������� ��������
class OrdinaryTreeNode: public AbstractTreeNode {
protected:
	int X0; // ����� �������
public:

	OrdinaryTreeNode() {
int r = 150;
this->buildSpace(r);



// ������� �������
frame = new ConcreteSubject(headOfList,0,"K0");
this->eProbe = new ObserverX(frame);
frame->observerX = eProbe;
} // SpecialTreeNode()
// ----------------------------------
Skip *getListOfSkip() {  // ���������� �������
	// ������ ������ � ���������� ������
	return headItemOfSkip;
	}

};  //  class Couple



//---------------------------------------------------------------------------
#endif
