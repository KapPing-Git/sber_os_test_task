#ifndef AGRAPHICS_MODEL_H
#define AGRAPHICS_MODEL_H

#include <QAbstractTableModel>
#include <QThread>
#include <QVector>

class AGraphics_model : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit AGraphics_model(QObject *parent = nullptr);

  void add_result(int count, int sum);
  void clear();

signals:

private:
  struct SResult
  {
    explicit SResult(int aCount, int aSum) {count = aCount; sum = aSum;}
    int count;
    int sum;
  };
  QVector<SResult> m_results;

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &) const override;
  virtual int columnCount(const QModelIndex &) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // AGRAPHICS_MODEL_H
