#include <gtest/gtest.h>
#include "./include/department.h"
#include "./include/shop.h"
#include "./include/dynamic_list.h"

// Тесты для класса Shop
TEST(ShopTest, DefaultConstructor) {
    Shop shop;
    EXPECT_EQ(shop.get_name(), "");
}

TEST(ShopTest, ConstructorWithName) {
    Shop shop("TestShop");
    EXPECT_EQ(shop.get_name(), "TestShop");
}

TEST(ShopTest, SetName) {
    Shop shop;
    shop.set_name("NewShop");
    EXPECT_EQ(shop.get_name(), "NewShop");
}

// Тесты для класса Dynamic_list
TEST(DynamicListTest, DefaultConstructor) {
    Dynamic_list<Shop> list;
    EXPECT_EQ(list.search("Test"), nullptr); // Список пуст
}

TEST(DynamicListTest, InsertElement) {
    Dynamic_list<Shop> list;
    list.insert_element("Shop1");
    list.insert_element("Shop2");
    list.insert_element("Shop0"); // Проверяем сортировку

    // Проверяем порядок элементов
    testing::internal::CaptureStdout();
    list.print_nodes();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Shop0\nShop1\nShop2\n");
}

TEST(DynamicListTest, SearchElement) {
    Dynamic_list<Shop> list;
    list.insert_element("Shop1");
    list.insert_element("Shop2");

    EXPECT_NE(list.search("Shop1"), nullptr);
    EXPECT_EQ(list.search("Shop3"), nullptr);
}

TEST(DynamicListTest, DeleteElement) {
    Dynamic_list<Shop> list;
    list.insert_element("Shop1");
    list.insert_element("Shop2");

    EXPECT_EQ(list.delete_element("Shop1"), "Shop1");
    EXPECT_EQ(list.delete_element("Shop3"), ""); // Не существует

    testing::internal::CaptureStdout();
    list.print_nodes();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Shop2\n");
}

TEST(DynamicListTest, CopyConstructor) {
    Dynamic_list<Shop> list;
    list.insert_element("Shop1");
    list.insert_element("Shop2");

    Dynamic_list<Shop> copy(list);
    testing::internal::CaptureStdout();
    copy.print_nodes();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Shop1\nShop2\n");

    // Проверяем, что изменение копии не влияет на оригинал
    copy.insert_element("Shop3");
    testing::internal::CaptureStdout();
    list.print_nodes();
    std::string original_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(original_output, "Shop1\nShop2\n");
}

TEST(DynamicListTest, AssignmentOperator) {
    Dynamic_list<Shop> list;
    list.insert_element("Shop1");
    list.insert_element("Shop2");

    Dynamic_list<Shop> other;
    other = list;

    testing::internal::CaptureStdout();
    other.print_nodes();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Shop1\nShop2\n");

    // Проверяем, что изменение копии не влияет на оригинал
    other.insert_element("Shop3");
    testing::internal::CaptureStdout();
    list.print_nodes();
    std::string original_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(original_output, "Shop1\nShop2\n");
}

TEST(DynamicListTest, MemoryLeakOnDestruction) {
    // Этот тест проверяет, что нет утечек памяти
    Dynamic_list<Shop>* list = new Dynamic_list<Shop>();
    list->insert_element("Shop1");
    list->insert_element("Shop2");
    delete list; // Проверяем, что деструктор корректно освобождает память
}

// Запуск тестов
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}