#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_plainTextEdit_textChanged();

    void on_pushButtonMatch_pressed();

    void on_comboBoxRegExp_editTextChanged(const QString &arg1);

    void on_plainTextEditTestText_textChanged();

private:
    void hilightMatched();


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
