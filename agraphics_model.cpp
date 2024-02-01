#include "agraphics_model.h"

AGraphics_model::AGraphics_model(QObject *parent)
  : QAbstractTableModel{parent}
{

}

void AGraphics_model::add_result(int count, int sum)
{
  beginInsertRows(QModelIndex(), m_results.count()+1, m_results.count()+1);
  m_results.append(SResult{count,sum});
  endInsertRows();
}

void AGraphics_model::clear()
{
  beginResetModel();
  m_results.clear();
  endResetModel();
}


int AGraphics_model::rowCount(const QModelIndex &) const
{
  return m_results.count();
}

int AGraphics_model::columnCount(const QModelIndex &) const
{
  return 2;
}

QVariant AGraphics_model::data(const QModelIndex &index, int role) const
{
  // Для Qt::DisplayRole возвращаем значение для соответствующего столбца и строки
  if (role == Qt::DisplayRole)
    {
      int row = index.row();
      switch (index.column())
        {
        case 0:
          return m_results[row].count;
          break;

        case 1:
          return m_results[row].sum;
          break;

        default:
          return QVariant{};
          break;
        }
    }
  else
    return QVariant{}; // для остальных ролей будут использованы значения по умолчанию
}


QVariant AGraphics_model::headerData(int section, Qt::Orientation orientation, int role) const
{
  if( role != Qt::DisplayRole )
    return QVariant();

  // По вертикали в заголовке номера строк
  if( orientation == Qt::Vertical )
    {
      return section + 1;
    }

  // По горизонтали в заголовке имена столбцов
  switch( section )
    {
    case 0:
      return "count";
    case 1:
      return "Summary";
    default:
      return QVariant{};
      break;
    }

  return QVariant();
}
