#pragma once


class QAbstractItemModel;
class QString;
class FileExportService {
public:
    // 定义为静态方法，Presenter 可以直接调用，不需要实例化
    static bool exportToCsv(QAbstractItemModel* model, const QString& filePath);
};