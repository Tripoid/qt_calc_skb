#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QList<QString> operators; // собирает все символы

// СЮДА НАДО ДОБАВИТЬ УСЛОВИЯ!!!
void MainWindow::displayResult(const QList<QString> &symbol) { //преобразует список в строку и выводит на экран
    QString resStr;
    for (int i = 0; i < symbol.size(); i+=1){
        resStr += symbol[i];
    }
    ui -> result -> setText(resStr);
}

void MainWindow::calcResult(const QList<QString> &opers){ //разделяет операнды и числа на два списка
    const QString numbers = "0123456789.";
    QString num;
    QList<float> nums;
    QList<QString> operands;
    int k = 0;
    for (int i = 0; i < opers.length(); i += 1) {
        if ((numbers.contains(opers[i], Qt::CaseInsensitive)) && (k == 0)) {
            num = opers[i];
            k += 1;
            qDebug() << num;
        }
        else if (numbers.contains(opers[i], Qt::CaseInsensitive) && k != 0 && numbers.contains(opers[i - 1], Qt::CaseInsensitive)) {
            num = num + opers[i];
            qDebug() << num;
        }
        else {
            k = 0;
            nums.append(num.toFloat());
            operands.append(opers[i]);//               НАПИСАТЬ ОТДЕЛЬНУЮ ФУНКЦИЮ ДОБАВЛЕНИЯ
        }
    }
    ui -> result -> setText(finalResult(operands, nums));
}

QString MainWindow::finalResult(QList<QString> &opers, QList<float> &nums) {//выполняет вычисления
    for (int i = 0; i < opers.length(); i += 1) {
        if (opers[i] == "%") {
            nums[i] = nums[i] / 100; // 5% - 8 +9%  988  -+
            opers.removeOne("%");
            i -= 1;
        }
    }

    for (int i = 0; i < opers.length(); i += 1) {
        if (opers[i] == "/") {
            nums[i] = nums[i] / nums[i+1];
            nums.removeAt(i+1);
            opers.removeOne("/");
            i -= 1;
        }
        else if (opers[i] == "*") {
            nums[i] = nums[i] * nums[i+1];
            nums.removeAt(i+1);
            opers.removeOne("*");
            i -= 1;
        }
    }

    for (int i = 0; i < opers.length(); i += 1) {
        if (opers[i] == "+") {
            nums[i] = nums[i] + nums[i+1];
            nums.removeAt(i+1);
            opers.removeOne("+");
            i -= 1;
        }
        else if (opers[i] == "-") {
            nums[i] = nums[i] - nums[i+1];
            nums.removeAt(i+1);
            opers.removeOne("-");
            i -= 1;
        }
    }
    return QString::number(nums[0]);
}

void MainWindow::addComponent(const QString &btnText) {  // добавление операндов с условиями
    const QString ops = "+-*/.";
    if (operators.size() == 0 || ((ops.contains(operators[operators.length()-1], Qt::CaseInsensitive) &&
        (ops.contains(btnText, Qt::CaseInsensitive) || btnText == "%")) ||
        (operators[operators.length()-1] == "%" && btnText == "%"))) { }
    else {
        operators.append(btnText);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e) // обработчик клавишь
{
    if (e -> key() == Qt::Key_0){
        operators.append("0");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_1){
        operators.append("1");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_2){
        operators.append("2");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_3){
        operators.append("3");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_4){
        operators.append("4");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_5){
        operators.append("5");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_6){
        operators.append("6");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_7){
        operators.append("7");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_8){
        operators.append("8");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_9){
        operators.append("9");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_Period){
        operators.append(".");
        displayResult(operators);
    }


    else if (e -> key() == Qt::Key_Plus){
        addComponent("+");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_Minus){
        addComponent("-");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_Slash){
        addComponent("/");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_Percent){
        addComponent("%");
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_Asterisk){
        addComponent("*");
        displayResult(operators);
    }

    else if (e -> key() == Qt::Key_Equal){
        operators.append("=");
        calcResult(operators);
        operators.clear();
    }
    else if (e -> key() == Qt::Key_Return){
        operators.append("=");
        calcResult(operators);
        operators.clear();
    }
    else if (e -> key() == Qt::Key_Backspace){
        if (operators.length() != 0) {
            operators.removeLast();
        }
        displayResult(operators);
    }
    else if (e -> key() == Qt::Key_Escape){
        ui -> result -> clear();
        operators.clear();
    }

}

void MainWindow::on_button1_clicked() // кнопка С
{
    ui -> result -> clear();
    operators.clear();
}


void MainWindow::on_button2_clicked() // кнопка убрать последний символ
{
    if (operators.length() != 0) {
        operators.removeLast();
    }
    displayResult(operators);
}


void MainWindow::on_button3_clicked() // кнопка %
{
    QString btnText = ui -> button3 -> text();
    addComponent(btnText);
    displayResult(operators);
}


void MainWindow::on_button4_clicked() // кнопка /
{
    QString btnText = ui -> button4 -> text();
    addComponent(btnText);
    displayResult(operators);
}


void MainWindow::on_button5_clicked() // 7
{
    QString btnText = ui -> button5 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button6_clicked() // 8
{
    QString btnText = ui -> button6 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button7_clicked() // 9
{
    QString btnText = ui -> button7 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button8_clicked() // кнопка *
{
    QString btnText = ui -> button8 -> text();
    addComponent(btnText);
    displayResult(operators);
}


void MainWindow::on_button9_clicked() // 4
{
    QString btnText = ui -> button9 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button10_clicked() // 5
{
    QString btnText = ui -> button10 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button11_clicked() // 6
{
    QString btnText = ui -> button11 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button12_clicked() // кнопка -
{
    QString btnText = ui -> button12 -> text();
    addComponent(btnText);
    displayResult(operators);
}


void MainWindow::on_button13_clicked() // 1
{
    QString btnText = ui -> button13 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button14_clicked() // 2
{
    QString btnText = ui -> button14 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button15_clicked() // 3
{
    QString btnText = ui -> button15 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button16_clicked() // кнопка +
{
    QString btnText = ui -> button16 -> text();
    addComponent(btnText);
    displayResult(operators);
}


void MainWindow::on_button17_clicked() // 0
{
    QString btnText = ui -> button17 -> text();
    operators.append(btnText);
    displayResult(operators);
}


void MainWindow::on_button18_clicked() // точка
{
    QString btnText = ui -> button18 -> text();
    addComponent(btnText);
    displayResult(operators);
}


void MainWindow::on_button19_clicked() //кнопка =
{
    QString btnText = ui -> button19 -> text();
    operators.append(btnText);
    calcResult(operators);
    operators.clear();
}
