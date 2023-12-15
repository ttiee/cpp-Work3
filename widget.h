#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void updateScoreLabel();
    void updateErrorLabel();

    void generateRandomLetter();
    // Qchar currentLetter;
    bool eventFilter(QObject* watched, QEvent* event);

private slots:
    void on_stackedWidget_currentChanged(int arg1);

    void on_pushButton_2_clicked();
    // void closeWindow();

    void on_pushButton_start_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    // Start *start = new Start(this);
};
#endif // WIDGET_H
