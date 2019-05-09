#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{

}

void MainWindow::on_plainTextEdit_textChanged()
{

}

void MainWindow::on_pushButtonMatch_pressed()
{
    hilightMatched();
}

void MainWindow::hilightMatched()
{
    QString strLog;

    auto textRegExp = ui->comboBoxRegExp->currentText();
    if (textRegExp.length() == 0) {
        ui->plainTextEditTestText->setExtraSelections(QList<QTextEdit::ExtraSelection>());
        ui->plainTextEditLog->setPlainText("");
        return;
    }

    QRegularExpression regExp(textRegExp);

    strLog += "Regular expression: " + textRegExp + "\n";
    auto textRegExpInSrc = textRegExp;
    textRegExp.replace("\\", "\\\\").replace("\"", "\\\"").replace("\'", "\\\'");
    strLog += "In C++ string literals: \"" + textRegExp + "\"\n";

    QTextCharFormat formatWhole;
    QBrush brush(Qt::GlobalColor::cyan);
    formatWhole.setBackground(brush);

    QTextCharFormat formatUnderline;
    formatUnderline.setUnderlineColor(Qt::GlobalColor::blue);
    formatUnderline.setUnderlineStyle(QTextCharFormat::UnderlineStyle::SingleUnderline);

    QList<QTextEdit::ExtraSelection> selections;
    auto textTest = ui->plainTextEditTestText->toPlainText();
    auto matchIter = regExp.globalMatch(textTest);

    if (matchIter.hasNext()) {
      strLog += "Matched!";
    } else {
        strLog += "Not matched.";
    }

    int indexMatch = 0;
    while (matchIter.hasNext()) {
        strLog += "Match #" + QString::number(indexMatch) + ":\n";
        auto match = matchIter.next();
        int lastCapturedIndex = match.lastCapturedIndex();
        for (int index = 0; index <= lastCapturedIndex; index ++) {
            int indexStart = match.capturedStart(index);
            int indexEnd = match.capturedEnd(index);
            auto strCaptured = match.captured(index);
            strLog += "Capture #" + QString::number(index) + ": start=" + QString::number(indexStart) + ", end=" + QString::number(indexEnd) + ", \"" + strCaptured + "\"" +  "\n";
            QTextCursor cursor(ui->plainTextEditTestText->document());
            cursor.setPosition(indexStart, QTextCursor::MoveMode::MoveAnchor);
            cursor.setPosition(indexEnd, QTextCursor::MoveMode::KeepAnchor);
            QTextEdit::ExtraSelection selection;
            selection.cursor = cursor;
            selection.format = (index == 0) ? formatWhole : formatUnderline;

            selections.append(selection);
        }
        indexMatch ++;
    }
    ui->plainTextEditTestText->setExtraSelections(selections);
    ui->plainTextEditLog->setPlainText(strLog);
}

void MainWindow::on_comboBoxRegExp_editTextChanged(const QString &arg1)
{
    hilightMatched();
}

void MainWindow::on_plainTextEditTestText_textChanged()
{
    hilightMatched();
}
