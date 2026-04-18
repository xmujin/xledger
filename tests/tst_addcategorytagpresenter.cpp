#include <QTest>
#include <QObject>
#include <gmock/gmock.h>
#include "addcategorytagpresenter.h"
#include "mockcategorymodel.h"
#include "mocktagmodel.h"
#include "mockaddcategorytagview.h"
#include <QList>
#include "categorydto.h"

using ::testing::_;      // 匹配符
using ::testing::Return; // 动作


class TestAddCategoryTagPresenter : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void onAddCategoryRequest_categoryExist();
	void onAddCategoryRequest_categoryNotExist();
protected:
    MockAddCategoryTagView view;
    MockCategoryModel categoryModel;
	MockTagModel tagModel;
};

void TestAddCategoryTagPresenter::onAddCategoryRequest_categoryExist()
{

    EXPECT_CALL(categoryModel, getCategories()).WillOnce(Return(QList<CategoryDto>()));
    EXPECT_CALL(tagModel, getTags()).WillOnce(Return(QList<TagDto>()));
    EXPECT_CALL(view, setCategory(_)).Times(1);
    EXPECT_CALL(view, setTag(_)).Times(1);

	AddCategoryTagPresenter presenter(&categoryModel, &tagModel, &view);
	EXPECT_CALL(categoryModel, isExist(QString("test"))).WillOnce(Return(true));
	EXPECT_CALL(view, showErrorMessage(QString("分类已存在"))).Times(1);

	presenter.onAddCategoryRequest("test");
}

void TestAddCategoryTagPresenter::onAddCategoryRequest_categoryNotExist()
{
    // --- 1. 为构造函数中的初始化行为编写预期 ---
        // 构造函数里调了这两个，必须先给它们安排好“剧本”
    EXPECT_CALL(categoryModel, getCategories()).WillOnce(Return(QList<CategoryDto>()));
    EXPECT_CALL(tagModel, getTags()).WillOnce(Return(QList<TagDto>()));
    EXPECT_CALL(view, setCategory(_)).Times(1);
    EXPECT_CALL(view, setTag(_)).Times(1);

    // --- 2. 现在创建对象，此时构造函数运行，匹配上面的预期，警告消失 ---
    AddCategoryTagPresenter presenter(&categoryModel, &tagModel, &view);

    // --- 3. 为接下来的逻辑编写预期 (onAddCategoryRequest) ---
    EXPECT_CALL(categoryModel, isExist(QString("test"))).WillOnce(Return(false));
    EXPECT_CALL(categoryModel, addCategory(QString("test"))).Times(1);
    EXPECT_CALL(categoryModel, getCategories()).WillOnce(Return(QList<CategoryDto>()));
    EXPECT_CALL(view, setCategory(_)).Times(1);

    // --- 4. 执行测试动作 ---
    presenter.onAddCategoryRequest("test");
}

void TestAddCategoryTagPresenter::initTestCase() {}
void TestAddCategoryTagPresenter::cleanupTestCase() {}


QTEST_MAIN(TestAddCategoryTagPresenter)
#include "tst_addcategorytagpresenter.moc"

