#ifndef ADATA_GENERATOR_H
#define ADATA_GENERATOR_H

#include <limits>

#include <QThread>
#include <QMutex>
#include <QRandomGenerator>
#include <QDateTime>

class AData_generator : public QThread
{
  Q_OBJECT
public:
  explicit AData_generator(QObject *parent = nullptr);
  ~AData_generator();
  void stop();

private:
  bool m_stop {false};
  bool m_terminate {false};
  QMutex m_mutex;
  QRandomGenerator m_rand_gen{uint32_t(QDateTime::currentDateTime().toMSecsSinceEpoch() % std::numeric_limits<uint32_t>::max())};

  const int MIN_GEN_VAL {0};
  const int MAX_GEN_VAL {100};

signals:
  void data_recieved(int value);

  // QThread interface
protected:
  virtual void run() override;
};

#endif // ADATA_GENERATOR_H
