#include "adata_generator.h"

AData_generator::AData_generator(QObject *parent)
  : QThread{parent}
{

}

AData_generator::~AData_generator()
{
  // Перед удалением ожидаем завершения потока
  m_mutex.lock();
  m_stop = true;
  m_terminate = true;
  m_mutex.unlock();
  wait();
}

void AData_generator::stop()
{
  // Запоминаем то что необходимо завершить поток
  m_stop = true;
}


void AData_generator::run()
{
  // Пока не придёт команда стоп генерируем случайные числа и отправляем их получателю
  // Не блокируем потоки, так как передача сигнал/слот потокобезопасна, а запись m_stop атомарная операция

  // Если сразу после старта объект удалён
  m_mutex.lock();
  if (!m_terminate)
    m_stop = false;
  m_mutex.unlock();

  while (!m_stop)
    {
      int val = m_rand_gen.bounded(MIN_GEN_VAL, MAX_GEN_VAL);
      emit data_recieved(val);
      msleep(10);
    }
}
