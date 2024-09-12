#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calcularDano();

private:
    QLineEdit *danos[5];
    QPushButton *calcularButton;
    QLabel *resultadoLabel;

    int calcularGolpesExtras(int &danoTotal, int *danosExtras);
};

#endif // MAINWINDOW_H
