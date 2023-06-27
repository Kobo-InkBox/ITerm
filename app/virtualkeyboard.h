#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>
#include <QFile>

namespace Ui {
class virtualkeyboard;
}

class virtualkeyboard : public QWidget
{
    Q_OBJECT

public:
    QString className = this->metaObject()->className();
    QString deviceID;
    QString keyboardText;
    explicit virtualkeyboard(QWidget *parent = nullptr);
    ~virtualkeyboard();
    bool shift = false;
    bool ctrl = false;
    bool shown = true;
    QString ctrlBtnStyleSheet;
    bool specialCharacters = false;
    bool embed;
    enum class keyboardMode {
        lowerCase,
        upperCase,
        specialCharacters,
    };
    void reverseKeys(keyboardMode keyboardMode);
    void setCtrl();
    void resetCtrl();
    QString readFile(QString file);

    Qt::Key currentKey;
    Qt::KeyboardModifier currentKeyboardModifier;
    QString currentText;

private slots:
    void on_shiftBtn_clicked();
    void on_ctrlBtn_clicked();
    void on_sat_clicked();
    void on_hideBtn_clicked();
    void on_showBtn_clicked();
    void adjust_size_function();

private:
    Ui::virtualkeyboard * ui;
    keyboardMode currentMode = keyboardMode::lowerCase;

signals:
    void adjust_size();
    void pressKey();
};

#endif // VIRTUALKEYBOARD_H
