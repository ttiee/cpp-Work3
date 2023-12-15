#include "widget.h"
#include "./ui_widget.h"
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QLabel>


int score = 0;
int error_n = 0;
// Qchar currentLetter;
QChar currentLetter;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // ui->stackedWidget->insertWidget(3, start);
    // ui->stackedWidget->setCurrentWidget(start);
    // connect(start, &Start::re_close, this, &Widget::closeWindow);

    ui->stackedWidget->setCurrentIndex(1);
    updateScoreLabel();
    updateErrorLabel();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_stackedWidget_currentChanged(int arg1)
{
    ;
}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Widget::on_pushButton_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_pushButton_clicked()
{
    // Clear previous letters and reset counts
    ui->label->clear();
    score = 0;
    error_n = 0;

    // Generate and display a random letter
    generateRandomLetter();

    // Update the labels
    updateScoreLabel();
    updateErrorLabel();

    // Install an event filter to capture key presses
    qApp->installEventFilter(this);
}

void Widget::generateRandomLetter()
{
    // Generate a random uppercase letter (A-Z)
    QChar randomLetter = QChar('A' + QRandomGenerator::global()->bounded(26));
    currentLetter = randomLetter;

    // Display the letter on the label
    ui->label->setText(QString(randomLetter));
}

bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // Check if the pressed key is correct
        if (keyEvent->text().toUpper() == currentLetter) {
            // Correct key pressed, update the score
            score++;
        } else {
            // Incorrect key pressed, update the error count
            error_n++;
        }

        // Generate and display a new random letter
        generateRandomLetter();

        // Update the labels
        updateScoreLabel();
        updateErrorLabel();

        return true; // Event handled
    }

    // Call the base class implementation
    return QWidget::eventFilter(watched, event);
}

void Widget::updateScoreLabel()
{
    // Update the score label text with the current score value
    ui->label_3->setText(QString("得分: %1").arg(score));
}

void Widget::updateErrorLabel()
{
    // Update the error label text with the current error value
    ui->label_2->setText(QString("失误: %1").arg(error_n));
}
