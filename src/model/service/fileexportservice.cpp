#include "fileexportservice.h"
#include <QFile>
#include <QTextStream>
#include <QStringConverter>
#include <QString>
#include <QAbstractItemModel>

bool FileExportService::exportToCsv(QAbstractItemModel* model, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out.setGenerateByteOrderMark(true); // 保证 Excel 打开不乱码

    // 添加表头
    for (int c = 0; c < model->columnCount(); ++c) {
        // 参数说明：列索引, 水平方向, 返回的数据角色
        QString header = model->headerData(c, Qt::Horizontal, Qt::DisplayRole).toString();
        out << header;

        if (c < model->columnCount() - 1) 
            out << ",";
    }
    out << "\n"; // 表头换行

    // 遍历行
    for (int r = 0; r < model->rowCount(); ++r) {
        // 遍历列
        for (int c = 0; c < model->columnCount(); ++c) {
            // 直接取值转字符串
            out << model->index(r, c).data().toString();

            // 如果不是最后一列，加逗号
            if (c < model->columnCount() - 1) out << ",";
        }
        out << "\n"; // 换行
    }

    file.close();
	return true;
}
