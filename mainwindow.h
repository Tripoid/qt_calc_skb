#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

    void on_button8_clicked();

    void on_button9_clicked();

    void on_button10_clicked();

    void on_button11_clicked();

    void on_button12_clicked();

    void on_button13_clicked();

    void on_button14_clicked();

    void on_button15_clicked();

    void on_button16_clicked();

    void on_button17_clicked();

    void on_button18_clicked();

    void on_button19_clicked();


public slots:
    void displayResult(const QList<QString> &symbol);
    void calcResult(const QList<QString> &opers);
    QString finalResult(QList<QString> &opers, QList<float> &nums);
    void addComponent(const QString &btnText);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
