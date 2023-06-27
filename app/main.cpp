#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QRegularExpression>
#include <QShortcut>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>

#include <qvterm.hpp>
#include <virtualkeyboard.h>

constexpr const char *urlMatch =
    R"((?:https?://|ftp://|news://|mailto:|file://|\bwww\.))"
    R"([\w\-\@;\/?:&=%\$.+!*\x27,~#]*)"
    "("
        R"(\([\w\-\@;\/?:&=%\$.+!*\x27,~#]*\))"
        "|"
        R"([\w\-\@;\/?:&=%\$+*~])"
    ")+";

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow win{};
    QWidget centralWidget{};
    QVBoxLayout layout{};
    QVTerm qvterm{};
    virtualkeyboard virtualKeyboard;

    layout.addWidget(&qvterm);
    layout.addWidget(&virtualKeyboard);
    layout.setStretch(0, 1); // Expand the terminal widget
    layout.setMargin(0);

    centralWidget.setLayout(&layout);
    win.setCentralWidget(&centralWidget);

    QString stylesheetFileString;
    if(std::getenv("STYLESHEET") != NULL) {
        stylesheetFileString = std::getenv("STYLESHEET");
    }
    else {
        stylesheetFileString = "/etc/eink.qss";
    }

    QFile stylesheetFile(stylesheetFileString);
    stylesheetFile.open(QFile::ReadOnly);
    win.setStyleSheet(stylesheetFile.readAll());
    stylesheetFile.close();

    win.show();

    qvterm.start();
    qvterm.setFocus();

    win.connect(&qvterm, &QVTerm::titleChanged, [&win](QString title) {
        win.setWindowTitle(title);
    });
    win.connect(&qvterm, &QVTerm::iconTextChanged, [&win](QString iconText) {
        win.setWindowIconText(iconText);
    });

    QShortcut pgup{QKeySequence{Qt::SHIFT + Qt::Key_PageUp}, &win};
    win.connect(&pgup, &QShortcut::activated, [&qvterm]() {
        qvterm.scrollPage(1);
    });
    QShortcut pgdown{QKeySequence{Qt::SHIFT + Qt::Key_PageDown}, &win};
    win.connect(&pgdown, &QShortcut::activated, [&qvterm]() {
        qvterm.scrollPage(-1);
    });

    QShortcut esc{QKeySequence{Qt::Key_Escape}, &win};
    win.connect(&esc, &QShortcut::activated, [&qvterm, &esc]() {
        qvterm.matchClear();
        esc.setEnabled(false);
    });
    esc.setEnabled(false);

    QShortcut findUrl{QKeySequence{Qt::CTRL + Qt::Key_M}, &win};
    win.connect(&findUrl, &QShortcut::activated, [&qvterm, &esc]() {
        static QRegularExpression re(urlMatch,
                QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);

        esc.setEnabled(true);
        qvterm.match(&re);
    });

    QObject::connect(&virtualKeyboard, &virtualkeyboard::pressKey, [&qvterm, &virtualKeyboard]() {
        qvterm.setFocus();
        if(virtualKeyboard.currentKeyboardModifier == Qt::ShiftModifier) {
            virtualKeyboard.currentText = virtualKeyboard.currentText.toUpper();
        }
        qvterm.pressKey(virtualKeyboard.currentKey, virtualKeyboard.currentKeyboardModifier, virtualKeyboard.currentText);
    });

    app.exec();

    return 0;
}
