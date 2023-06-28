#include "virtualkeyboard.h"
#include "ui_virtualkeyboard.h"

#include <QTimer>
#include <QScreen>
#include <QDebug>

virtualkeyboard::virtualkeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::virtualkeyboard)
{   
    ui->setupUi(this);
    ui->showBtn->hide();

    this->setFont(QFont("Inter"));
    deviceID = QString(std::getenv("DEVICE"));

    embed = false;

    ui->n1->setProperty("type", "borderless");
    ui->n2->setProperty("type", "borderless");
    ui->n3->setProperty("type", "borderless");
    ui->n4->setProperty("type", "borderless");
    ui->n5->setProperty("type", "borderless");
    ui->n6->setProperty("type", "borderless");
    ui->n7->setProperty("type", "borderless");
    ui->n8->setProperty("type", "borderless");
    ui->n9->setProperty("type", "borderless");
    ui->n0->setProperty("type", "borderless");

    ui->la->setProperty("type", "borderless");
    ui->lb->setProperty("type", "borderless");
    ui->lc->setProperty("type", "borderless");
    ui->ld->setProperty("type", "borderless");
    ui->le->setProperty("type", "borderless");
    ui->lf->setProperty("type", "borderless");
    ui->lg->setProperty("type", "borderless");
    ui->lh->setProperty("type", "borderless");
    ui->li->setProperty("type", "borderless");
    ui->lj->setProperty("type", "borderless");
    ui->lk->setProperty("type", "borderless");
    ui->ll->setProperty("type", "borderless");
    ui->lm->setProperty("type", "borderless");
    ui->ln->setProperty("type", "borderless");
    ui->lo->setProperty("type", "borderless");
    ui->lp->setProperty("type", "borderless");
    ui->lq->setProperty("type", "borderless");
    ui->lr->setProperty("type", "borderless");
    ui->ls->setProperty("type", "borderless");
    ui->lt->setProperty("type", "borderless");
    ui->lu->setProperty("type", "borderless");
    ui->lv->setProperty("type", "borderless");
    ui->lw->setProperty("type", "borderless");
    ui->lx->setProperty("type", "borderless");
    ui->ly->setProperty("type", "borderless");
    ui->lz->setProperty("type", "borderless");

    ui->eraseBtn->setProperty("type", "borderless");
    ui->shiftBtn->setProperty("type", "borderless");
    ui->ctrlBtn->setProperty("type", "borderless");
    ui->escBtn->setProperty("type", "borderless");
    ui->slashBtn->setProperty("type", "borderless");
    ui->homeBtn->setProperty("type", "borderless");
    ui->leftArrowBtn->setProperty("type", "borderless");
    ui->upArrowBtn->setProperty("type", "borderless");
    ui->downArrowBtn->setProperty("type", "borderless");
    ui->endBtn->setProperty("type", "borderless");
    ui->rightArrowBtn->setProperty("type", "borderless");
    ui->pageUpBtn->setProperty("type", "borderless");
    ui->pageDownBtn->setProperty("type", "borderless");
    ui->enterBtn->setProperty("type", "borderless");
    ui->spt->setProperty("type", "borderless");
    ui->sat->setProperty("type", "borderless");
    ui->hideBtn->setProperty("type", "borderless");

    // Credit ChatGPT for the weird conditional expressions, not me
    connect(ui->enterBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Return; currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); resetCtrl(); });
    connect(ui->tabBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Space; currentKeyboardModifier = Qt::NoModifier; currentText = "\t"; emit pressKey(); });
    connect(ui->escBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Escape; currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->slashBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Space; currentKeyboardModifier = Qt::NoModifier; currentText = "/"; emit pressKey(); });
    connect(ui->homeBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Home, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->leftArrowBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Left, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->upArrowBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Up, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->downArrowBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Down, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->endBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_End, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->rightArrowBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Right, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->pageUpBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_PageUp, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->pageDownBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_PageDown, currentKeyboardModifier = Qt::NoModifier; currentText = ""; emit pressKey(); });
    connect(ui->spaceBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Space; currentKeyboardModifier = Qt::NoModifier; currentText = " "; emit pressKey(); });
    connect(ui->eraseBtn, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Backspace, currentKeyboardModifier = Qt::NoModifier; currentText = "", emit pressKey(); });
    connect(ui->spt, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Period; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "."; emit pressKey(); resetCtrl(); });

    connect(ui->n1, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_1; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "1"; emit pressKey(); resetCtrl(); });
    connect(ui->n2, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_2; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "2"; emit pressKey(); resetCtrl(); });
    connect(ui->n3, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_3; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "3"; emit pressKey(); resetCtrl(); });
    connect(ui->n4, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_4; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "4"; emit pressKey(); resetCtrl(); });
    connect(ui->n5, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_5; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "5"; emit pressKey(); resetCtrl(); });
    connect(ui->n6, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_6; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "6"; emit pressKey(); resetCtrl(); });
    connect(ui->n7, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_7; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "7"; emit pressKey(); resetCtrl(); });
    connect(ui->n8, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_8; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "8"; emit pressKey(); resetCtrl(); });
    connect(ui->n9, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_9; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "9"; emit pressKey(); resetCtrl(); });
    connect(ui->n0, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_0; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = "0"; emit pressKey(); resetCtrl(); });

    connect(ui->la, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_A; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "\"" : "a"; emit pressKey(); resetCtrl(); });
    connect(ui->lb, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_B; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "]" : "b"; emit pressKey(); resetCtrl(); });
    connect(ui->lc, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_C; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "}" : "c"; emit pressKey(); resetCtrl(); });
    connect(ui->ld, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_D; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? ":" : "d"; emit pressKey(); resetCtrl(); });
    connect(ui->le, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_E; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "€" : "e"; emit pressKey(); resetCtrl(); });
    connect(ui->lf, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_F; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? ";" : "f"; emit pressKey(); resetCtrl(); });
    connect(ui->lg, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_G; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "!" : "g"; emit pressKey(); resetCtrl(); });
    connect(ui->lh, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_H; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "?" : "h"; emit pressKey(); resetCtrl(); });
    connect(ui->li, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_I; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "(" : "i"; emit pressKey(); resetCtrl(); });
    connect(ui->lj, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_J; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "," : "j"; emit pressKey(); resetCtrl(); });
    connect(ui->lk, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_K; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "_" : "k"; emit pressKey(); resetCtrl(); });
    connect(ui->ll, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_L; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "|" : "l"; emit pressKey(); resetCtrl(); });
    connect(ui->lm, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_M; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? ">" : "m"; emit pressKey(); resetCtrl(); });
    connect(ui->ln, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_N; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "<" : "n"; emit pressKey(); resetCtrl(); });
    connect(ui->lo, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_O; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? ")" : "o"; emit pressKey(); resetCtrl(); });
    connect(ui->lp, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_P; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "*" : "p"; emit pressKey(); resetCtrl(); });
    connect(ui->lq, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Q; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "@" : "q"; emit pressKey(); resetCtrl(); });
    connect(ui->lr, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_R; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "%" : "r"; emit pressKey(); resetCtrl(); });
    connect(ui->ls, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_S; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "'" : "s"; emit pressKey(); resetCtrl(); });
    connect(ui->lt, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_T; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "&&" : "t"; emit pressKey(); resetCtrl(); });
    connect(ui->lu, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_U; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "+" : "u"; emit pressKey(); resetCtrl(); });
    connect(ui->lv, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_V; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "[" : "v"; emit pressKey(); resetCtrl(); });
    connect(ui->lw, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_W; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "#" : "w"; emit pressKey(); resetCtrl(); });
    connect(ui->lx, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_X; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "{" : "x"; emit pressKey(); resetCtrl(); });
    connect(ui->ly, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Y; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "-" : "y"; emit pressKey(); resetCtrl(); });
    connect(ui->lz, &QPushButton::clicked, this, [this]() { currentKey = Qt::Key_Z; currentKeyboardModifier = (ctrl) ? Qt::ControlModifier : (shift) ? Qt::ShiftModifier : Qt::NoModifier; currentText = (specialCharacters) ? "~" : "z"; emit pressKey(); resetCtrl(); });

    if(deviceID == "n873") {
        ui->n1->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n2->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n3->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n4->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n5->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n6->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n7->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n8->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n9->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->n0->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");

        ui->la->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lb->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lc->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->ld->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->le->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lf->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lg->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lh->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->li->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lj->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lk->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->ll->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lm->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->ln->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lo->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lp->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lq->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lr->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->ls->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lt->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lu->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lv->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lw->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lx->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->ly->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->lz->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");

        ui->eraseBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->shiftBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->ctrlBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->escBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->tabBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->slashBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->homeBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->leftArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->upArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->downArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->endBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->rightArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->pageUpBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->pageDownBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->hideBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 19.5px; padding-bottom: 19.5px; padding-left: 25px; padding-right: 25px; border: 1px solid black");
        ui->showBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 19.5px; padding-bottom: 19.5px; padding-left: 25px; padding-right: 25px; border: 1px solid black");
        ui->spt->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 27px");
        ui->sat->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 27px");
        ui->spaceBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 15px; border: 1px solid black");
        ui->enterBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding-top: 15px; padding-bottom: 15px; padding-left: 60px; padding-right: 60px; border: 1px solid black");
    }
    else if(deviceID == "n437") {
        ui->n1->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n2->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n3->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n4->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n5->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n6->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n7->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n8->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n9->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->n0->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");

        ui->la->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lb->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lc->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->ld->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->le->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lf->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lg->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lh->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->li->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lj->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lk->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->ll->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lm->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->ln->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lo->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lp->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lq->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lr->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->ls->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lt->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lu->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lv->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lw->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lx->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->ly->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->lz->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");

        ui->eraseBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->shiftBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->ctrlBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->escBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->tabBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->slashBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->homeBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->leftArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->upArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->downArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->endBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->rightArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->pageUpBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->pageDownBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 15px; border: 1px solid black");
        ui->hideBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 20px; padding-bottom: 20px; padding-left: 25px; padding-right: 25px; border: 1px solid black");
        ui->showBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 20px; padding-bottom: 20px; padding-left: 25px; padding-right: 25px; border: 1px solid black");
        ui->spt->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 20px");
        ui->sat->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 20px");
        ui->spaceBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 15px; border: 1px solid black");
        ui->enterBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding-top: 15px; padding-bottom: 15px; padding-left: 60px; padding-right: 60px; border: 1px solid black");
    }
    else if(deviceID == "n705") {
        ui->n1->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n2->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n3->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n4->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n5->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n6->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n7->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n8->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n9->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->n0->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");

        ui->la->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lb->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lc->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->ld->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->le->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lf->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lg->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lh->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->li->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lj->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lk->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->ll->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lm->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->ln->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lo->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lp->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lq->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lr->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->ls->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lt->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lu->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lv->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lw->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lx->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->ly->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->lz->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");

        ui->eraseBtn->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->shiftBtn->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->ctrlBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->escBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->tabBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->slashBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->homeBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->leftArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->upArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->downArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->endBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->rightArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->pageUpBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->pageDownBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->hideBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 12px; padding-bottom: 12px; padding-left: 20px; padding-right: 20px; border: 1px solid black");
        ui->showBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 15px; padding-bottom: 15px; padding-left: 20px; padding-right: 20px; border: 1px solid black");
        ui->spt->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 11.45px");
        ui->sat->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 11.45px");
        ui->spaceBtn->setStyleSheet("font-weight: bold; font-size: 8pt; padding: 10px; border: 1px solid black");
        ui->enterBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding-top: 10px; padding-bottom: 10px; padding-left: 60px; padding-right: 60px; border: 1px solid black");
    }
    else {
        ui->n1->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n2->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n3->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n4->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n5->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n6->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n7->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n8->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n9->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->n0->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");

        ui->la->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lb->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lc->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->ld->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->le->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lf->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lg->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lh->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->li->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lj->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lk->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->ll->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lm->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->ln->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lo->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lp->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lq->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lr->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->ls->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lt->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lu->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lv->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lw->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lx->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->ly->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->lz->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");

        ui->eraseBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->shiftBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->ctrlBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->escBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->tabBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->slashBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->homeBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->leftArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->upArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->downArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->endBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->rightArrowBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->pageUpBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->pageDownBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 10px; border: 1px solid black");
        ui->hideBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 13px; padding-bottom: 13px; padding-left: 20px; padding-right: 20px; border: 1px solid black");
        ui->showBtn->setStyleSheet("font-weight: bold; font-size: 7pt; padding-top: 10px; padding-bottom: 10px; padding-left: 20px; padding-right: 20px; border: 1px solid black");
        ui->spt->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 13px");
        ui->sat->setStyleSheet("font-weight: bold; font-size: 7pt; padding: 13px");
        ui->spaceBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding: 10px; border: 1px solid black");
        ui->enterBtn->setStyleSheet("font-weight: bold; font-size: 9pt; padding-top: 10px; padding-bottom: 10px; padding-left: 60px; padding-right: 60px; border: 1px solid black");
    }
    ctrlBtnStyleSheet = ui->ctrlBtn->styleSheet();

    if(embed == false) {
        adjust_size_function();
    }
}

virtualkeyboard::~virtualkeyboard()
{
    delete ui;
}

void virtualkeyboard::on_shiftBtn_clicked()
{
    if(shift == true) {
        shift = false;
        reverseKeys(keyboardMode::lowerCase);
    }
    else {
        reverseKeys(keyboardMode::upperCase);
        shift = true;
    }

}

void virtualkeyboard::on_ctrlBtn_clicked() {
    if(ctrl == false) {
        setCtrl();
    }
    else {
        resetCtrl();
    }
}

void virtualkeyboard::setCtrl() {
    ui->ctrlBtn->setStyleSheet(ctrlBtnStyleSheet + "; color: white; background-color: black");
    ctrl = true;
}

void virtualkeyboard::resetCtrl() {
    ui->ctrlBtn->setStyleSheet(ctrlBtnStyleSheet + "; color: black; background-color: white");
    ctrl = false;
}

void virtualkeyboard::on_sat_clicked() {
    if(specialCharacters == true) {
        specialCharacters = false;
        reverseKeys(keyboardMode::lowerCase);
    }
    else {
        reverseKeys(keyboardMode::specialCharacters);
        specialCharacters = true;
    }
}

void virtualkeyboard::reverseKeys(keyboardMode keyboardMode) {
    currentMode = keyboardMode;
    if(keyboardMode == keyboardMode::upperCase) {
        ui->shiftBtn->setText("⇪");
        ui->n1->setText("1");
        ui->n2->setText("2");
        ui->n3->setText("3");
        ui->n4->setText("4");
        ui->n5->setText("5");
        ui->n6->setText("6");
        ui->n7->setText("7");
        ui->n8->setText("8");
        ui->n9->setText("9");
        ui->n0->setText("0");

        ui->la->setText("A");
        ui->lb->setText("B");
        ui->lc->setText("C");
        ui->ld->setText("D");
        ui->le->setText("E");
        ui->lf->setText("F");
        ui->lg->setText("G");
        ui->lh->setText("H");
        ui->li->setText("I");
        ui->lj->setText("J");
        ui->lk->setText("K");
        ui->ll->setText("L");
        ui->lm->setText("M");
        ui->ln->setText("N");
        ui->lo->setText("O");
        ui->lp->setText("P");
        ui->lq->setText("Q");
        ui->lr->setText("R");
        ui->ls->setText("S");
        ui->lt->setText("T");
        ui->lu->setText("U");
        ui->lv->setText("V");
        ui->lw->setText("W");
        ui->lx->setText("X");
        ui->ly->setText("Y");
        ui->lz->setText("Z");
    }
    else if(keyboardMode == keyboardMode::lowerCase) {
        ui->shiftBtn->setText("⇧");

        ui->n1->setText("1");
        ui->n2->setText("2");
        ui->n3->setText("3");
        ui->n4->setText("4");
        ui->n5->setText("5");
        ui->n6->setText("6");
        ui->n7->setText("7");
        ui->n8->setText("8");
        ui->n9->setText("9");
        ui->n0->setText("0");

        ui->la->setText("a");
        ui->lb->setText("b");
        ui->lc->setText("c");
        ui->ld->setText("d");
        ui->le->setText("e");
        ui->lf->setText("f");
        ui->lg->setText("g");
        ui->lh->setText("h");
        ui->li->setText("i");
        ui->lj->setText("j");
        ui->lk->setText("k");
        ui->ll->setText("l");
        ui->lm->setText("m");
        ui->ln->setText("n");
        ui->lo->setText("o");
        ui->lp->setText("p");
        ui->lq->setText("q");
        ui->lr->setText("r");
        ui->ls->setText("s");
        ui->lt->setText("t");
        ui->lu->setText("u");
        ui->lv->setText("v");
        ui->lw->setText("w");
        ui->lx->setText("x");
        ui->ly->setText("y");
        ui->lz->setText("z");
    }
    else if(keyboardMode == keyboardMode::specialCharacters) {
        ui->shiftBtn->setText("⇧");

        ui->n1->setText("1");
        ui->n2->setText("2");
        ui->n3->setText("3");
        ui->n4->setText("4");
        ui->n5->setText("5");
        ui->n6->setText("6");
        ui->n7->setText("7");
        ui->n8->setText("8");
        ui->n9->setText("9");
        ui->n0->setText("0");

        ui->lq->setText("@");
        ui->lw->setText("#");
        ui->le->setText("€");
        ui->lr->setText("%");
        // Important
        ui->lt->setText("&&");
        ui->ly->setText("-");
        ui->lu->setText("+");
        ui->li->setText("(");
        ui->lo->setText(")");
        ui->lp->setText("*");
        // Important
        ui->la->setText("\"");
        ui->ls->setText("'");
        ui->ld->setText(":");
        ui->lf->setText(";");
        ui->lg->setText("!");
        ui->lh->setText("?");
        ui->lj->setText(",");
        ui->lk->setText("_");
        ui->ll->setText("|");
        ui->lz->setText("~");

        ui->lx->setText("{");
        ui->lc->setText("}");
        ui->lv->setText("[");
        ui->lb->setText("]");
        ui->ln->setText("<");
        ui->lm->setText(">");
    }
    QTimer::singleShot(1000, this, SLOT(adjust_size_function()));
}

void virtualkeyboard::on_hideBtn_clicked() {
    shown = false;
    ui->mainWidget->hide();
    ui->showBtn->show();
    adjust_size_function();
}

void virtualkeyboard::on_showBtn_clicked() {
    shown = true;
    ui->showBtn->hide();
    ui->mainWidget->show();
    adjust_size_function();
}

void virtualkeyboard::adjust_size_function() {
    if(embed == true) {
        emit adjust_size();
    }
    else {
        float keyboardScaleFactor;
        if(shown) {
            if(std::getenv("KEYBOARD_SCALING_FACTOR") != NULL) {
                keyboardScaleFactor = std::atof(std::getenv("KEYBOARD_SCALING_FACTOR"));
            }
            else {
                keyboardScaleFactor = 47;
            }
        }
        else {
            keyboardScaleFactor = 100 * (1.6 * ui->showBtn->size().height()) / QGuiApplication::screens()[0]->size().height();
        }
        this->setFixedHeight(QGuiApplication::screens()[0]->size().height() * keyboardScaleFactor / 100);
        this->setFixedWidth(QGuiApplication::screens()[0]->size().width());
        this->move(0, (QGuiApplication::screens()[0]->size().height() - this->height()));
    }
}

QString virtualkeyboard::readFile(QString file) {
    if(QFile::exists(file)) {
        QFile fileToRead(file);
        fileToRead.open(QIODevice::ReadOnly);
        QTextStream in (&fileToRead);
        QString content = in.readAll();
        return content;
    }
    else {
        return NULL;
    }
}
