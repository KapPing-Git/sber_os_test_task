#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Настраиваем график
  ui->chart_view->chart()->addSeries(m_series);
  m_axisX->setRange(0, 1);
  m_axisX->setLabelFormat("%.2f");
  ui->chart_view->chart()->addAxis(m_axisX, Qt::AlignBottom);
  m_series->attachAxis(m_axisX);

  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(0, 100);
  axisY->setLabelFormat("%.2f");
  ui->chart_view->chart()->addAxis(axisY, Qt::AlignLeft);
  m_series->attachAxis(axisY);

  ui->chart_view->setRenderHint(QPainter::Antialiasing);
  m_gen->start();

  // Соединяем генератор с получателем данных
  connect(m_gen, &AData_generator::data_recieved, this, &MainWindow::on_data_recieved);

  // Устанавливаем модель статистики для отображения
  ui->tableView->setModel(m_stat_model);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_start_stop_button_clicked()
{
  if (!m_gen->isRunning())
    m_gen->start();
  else
    m_gen->stop();
}


void MainWindow::on_reset_button_clicked()
{
  m_series->clear();
  m_curr_sum = 0;
}

void MainWindow::on_data_recieved(int value)
{
  // Получаем данные от генератора и добавляем их в график
  m_series->append(m_series->count(), value);
  m_curr_sum += value;
  m_axisX->setRange(0, m_series->count() + 1);
}


void MainWindow::on_save_button_clicked()
{
  // Добавляем порцию данных в модель
  m_stat_model->add_result(m_series->count(), m_curr_sum);
}


void MainWindow::on_clear_button_clicked()
{
  m_stat_model->clear();
}

