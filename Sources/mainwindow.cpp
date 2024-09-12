#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Criação dos QLineEdits para entrada de dados
    for (int i = 0; i < 5; ++i) {
        danos[i] = new QLineEdit(this);
        danos[i]->setPlaceholderText(QString("Dano Ataque %1").arg(i + 1));
        layout->addWidget(danos[i]);
    }

    calcularButton = new QPushButton("Calcular", this);
    layout->addWidget(calcularButton);

    resultadoLabel = new QLabel(this);
    layout->addWidget(resultadoLabel);

    setCentralWidget(centralWidget);

    connect(calcularButton, &QPushButton::clicked, this, &MainWindow::calcularDano);
}

MainWindow::~MainWindow() {}

void MainWindow::calcularDano() {
    bool ok;
    int danosAtaques[5];
    int totalDano = 0;

    // Leitura dos valores inseridos
    for (int i = 0; i < 5; ++i) {
        danosAtaques[i] = danos[i]->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Erro", "Por favor insira valores válidos para todos os danos.");
            return;
        }
        totalDano += danosAtaques[i];
    }

    // Array para armazenar os danos dos golpes extras
    int danosExtras[3] = {0}; // Máximo de 3 golpes extras
    int golpesExtras = calcularGolpesExtras(totalDano, danosExtras);

    QString resultado = QString("Dano total causado: %1\n").arg(totalDano);
    resultado += QString("Golpes extras realizados: %1\n").arg(golpesExtras);
    for (int i = 0; i < golpesExtras; ++i) {
        resultado += QString("Dano do golpe extra %1: %2\n").arg(i + 1).arg(danosExtras[i]);
    }

    resultadoLabel->setText(resultado);
}

int MainWindow::calcularGolpesExtras(int &danoTotal, int *danosExtras) {
    int golpesExtras = 0;
    for (int i = 0; i < 3; ++i) {
        if (QRandomGenerator::global()->bounded(100) < 60) {
            // Calcular dano do golpe extra (1d6)
            int danoGolpeExtra = QRandomGenerator::global()->bounded(1, 7);
            danosExtras[i] = danoGolpeExtra;
            danoTotal += danoGolpeExtra; // Adiciona o dano do golpe extra ao total
            golpesExtras++;
        } else {
            break;
        }
    }
    return golpesExtras;
}
