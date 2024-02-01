#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include <QValueAxis>

#include "adata_generator.h"
#include "agraphics_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_start_stop_button_clicked();
  void on_reset_button_clicked();
  void on_data_recieved(int value);

  void on_save_button_clicked();

  void on_clear_button_clicked();

private:
  Ui::MainWindow *ui;
  AData_generator *m_gen = new AData_generator{this};
  AGraphics_model *m_stat_model = new AGraphics_model{this};

  QLineSeries* m_series = new QLineSeries();
  QValueAxis *m_axisX = new QValueAxis;

  int m_curr_sum {0};
};
#endif // MAINWINDOW_H
