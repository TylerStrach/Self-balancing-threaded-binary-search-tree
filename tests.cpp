#include <gtest/gtest.h>
#include "mymap.h"
#include <random> // for rand

// tests default constructor and size
TEST(mymap, defaultConstructor_and_Size) {
    mymap<int, int> intTest;
    EXPECT_EQ(intTest.Size(), 0);

    mymap<string, string> stringTest;
    EXPECT_EQ(stringTest.Size(), 0);

    mymap<int, string> mixTest1;
    EXPECT_EQ(mixTest1.Size(), 0);

    mymap<char, int> mixTest2;
    EXPECT_EQ(mixTest2.Size(), 0);

    mymap<string, char> mixTest3;
    EXPECT_EQ(mixTest3.Size(), 0);

    mymap<double, bool> mixTest4;
    EXPECT_EQ(mixTest4.Size(), 0);

    mymap<int, double> mixTest5;
    EXPECT_EQ(mixTest5.Size(), 0);
}

// tests default put and size
TEST(mymap, put_and_Size){
    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};

    for (int i = 0; i < n; i++){
        EXPECT_EQ(intTest.Size(), i);
        intTest.put(arr[i], arr[i]);
    }
    ASSERT_EQ(intTest.Size(), n);

    mymap<double, bool> mixTest;
    n = 10;
    double arr2[] = {30.5, 15, 50.5, 8.5, 25, 70, 20.5, 28, 40.5, 60.5};
    bool arr3[] = {true, false, true, true, false, false, true, false, true, true};
    for (int i = 0; i < n; i++){
        EXPECT_EQ(mixTest.Size(), i);
        mixTest.put(arr2[i], arr3[i]);
    }
    ASSERT_EQ(mixTest.Size(), n);

    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);

    ASSERT_EQ(mixDupTest.Size(), 3);
}

// tests contains
TEST(mymap, contains){
    mymap<bool, bool> emptyTest;
    EXPECT_FALSE(emptyTest.contains(true));
    EXPECT_FALSE(emptyTest.contains(false));

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++){
        EXPECT_EQ(intTest.Size(), i);
        intTest.put(arr[i], arr[i]);
    }
    EXPECT_EQ(intTest.Size(), n);
    for (int i = 0; i < n; i++)
        EXPECT_TRUE(intTest.contains(arr[i]));
    EXPECT_FALSE(intTest.contains(100));
    EXPECT_FALSE(intTest.contains(-50));


    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    EXPECT_EQ(mixDupTest.Size(), 3);
    for (int i = 0; i < n; i++)
        EXPECT_TRUE(mixDupTest.contains(arr4[i]));
    EXPECT_FALSE(mixDupTest.contains("peter"));
    EXPECT_FALSE(mixDupTest.contains("steve"));

    mymap<int, int> largeRandTest;
    n = 100;
    for(int i = 0; i < n; i++){
        int key = rand() % 500;
        largeRandTest.put(key, rand() % 500);
        ASSERT_TRUE(largeRandTest.contains(key));
    }
}

// tests get function
TEST(mymap, get){
    mymap<char, bool> emptyTest;
    ASSERT_EQ(emptyTest.get('a'), 0);
    ASSERT_EQ(emptyTest.get('0'), 0);

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++){
        EXPECT_EQ(intTest.Size(), i);
        intTest.put(arr[i], arr[i]);
    }
    EXPECT_EQ(intTest.Size(), n);
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(intTest.get(arr[i]), arr[i]);
        EXPECT_EQ(intTest.Size(), n);
    }

    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    EXPECT_EQ(mixDupTest.Size(), 3);
    EXPECT_EQ(mixDupTest.get(arr4[1]), 6);
    EXPECT_EQ(mixDupTest.get(arr4[0]), 20);
    EXPECT_EQ(mixDupTest.get(arr4[4]), 20);
    EXPECT_EQ(mixDupTest.get(arr4[2]), 15);
    EXPECT_EQ(mixDupTest.get(arr4[3]), 15);

    mymap<int, int> largeRandTest;
    n = 100;
    for(int i = 0; i < n; i++){
        int key = rand() % 500;
        int val = rand() % 500;
        largeRandTest.put(key, val);
        ASSERT_EQ(largeRandTest.get(key), val);
    }
}

// tests toString function
TEST(mymap, toString){
    mymap<float, float> emptyTest;
    ASSERT_EQ(emptyTest.toString(), "");

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++){
        EXPECT_EQ(intTest.Size(), i);
        intTest.put(arr[i], arr[i]);
    }
    string test = "key: 8 value: 8\n"
                  "key: 15 value: 15\n"
                  "key: 20 value: 20\n"
                  "key: 25 value: 25\n"
                  "key: 28 value: 28\n"
                  "key: 30 value: 30\n"
                  "key: 40 value: 40\n"
                  "key: 50 value: 50\n"
                  "key: 60 value: 60\n"
                  "key: 70 value: 70\n";
    EXPECT_EQ(intTest.Size(), n);
    ASSERT_EQ(intTest.toString(), test);

    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    test = "key: edward value: 6\n"
           "key: strach value: 15\n"
           "key: tyler value: 20\n";
    ASSERT_EQ(mixDupTest.toString(), test);

    mymap<double, bool> mixDupTest2;
    n = 10;
    double arr2[] = {30.5, 15, 50.5, 15, 25, 70, 15, 28, 50.5, 60.5};
    bool arr3[] = {true, false, true, true, false, false, true, false, true, true};
    for (int i = 0; i < n; i++)
        mixDupTest2.put(arr2[i], arr3[i]);
    test = "key: 15 value: 1\n"
            "key: 25 value: 0\n"
            "key: 28 value: 0\n"
            "key: 30.5 value: 1\n"
            "key: 50.5 value: 1\n"
            "key: 60.5 value: 1\n"
            "key: 70 value: 0\n";
    ASSERT_EQ(mixDupTest2.toString(), test);

    mymap<int, int> randTest1;
    mymap<int, int> randTest2;
    for(int i = 0; i < 50; i++){
        int rKey = rand() % 100;
        int rVal = rand() % 100;
        randTest1.put(rKey, rVal);
        randTest2.put(rKey, rVal);
    }
    ASSERT_EQ(randTest1.toString(), randTest2.toString());
}

// tests accessOperator function
TEST(mymap, accessOperator){
    mymap<double, string> emptyTest;
    EXPECT_EQ(emptyTest[9.3], "");
    EXPECT_EQ(emptyTest[34.5], "");

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++)
        intTest.put(arr[i], arr[i]);
    for(int i = 0; i < n; i++)
        EXPECT_EQ(intTest[arr[i]], arr[i]);
    ASSERT_EQ(intTest[100], 0);
    ASSERT_EQ(intTest[-100], 0);
    ASSERT_EQ(intTest.Size(), n+2);
    string test = "key: -100 value: 0\n"
                  "key: 8 value: 8\n"
                  "key: 15 value: 15\n"
                  "key: 20 value: 20\n"
                  "key: 25 value: 25\n"
                  "key: 28 value: 28\n"
                  "key: 30 value: 30\n"
                  "key: 40 value: 40\n"
                  "key: 50 value: 50\n"
                  "key: 60 value: 60\n"
                  "key: 70 value: 70\n"
                  "key: 100 value: 0\n";
    ASSERT_EQ(intTest.toString(), test);

    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    EXPECT_EQ(mixDupTest[arr4[0]], 20);
    EXPECT_EQ(mixDupTest[arr4[1]], 6);
    EXPECT_EQ(mixDupTest[arr4[2]], 15);
    EXPECT_EQ(mixDupTest[arr4[3]], 15);
    EXPECT_EQ(mixDupTest[arr4[4]], 20);
    EXPECT_EQ(mixDupTest["peter"], 0);
    EXPECT_EQ(mixDupTest["albert"], 0);
    EXPECT_EQ(mixDupTest.Size(), 5);

    mymap<int, int> largeRand;
    n = 50;
    largeRand.put(3333, 3333);
    for(int i = 0; i < n; i++){
        largeRand.put(rand() % 100, rand() % 300);
    }
    EXPECT_EQ(largeRand[3333], 3333);
    for(int i = 0; i < n; i++){
        if(largeRand.contains(i)){
            EXPECT_EQ(largeRand[i], largeRand.get(i));
        }
    }
}

// tests begin and increment functions from the iterator struct
TEST(mymap, begin_and_increment){
    mymap<float, char> emptyTest;
    for(auto key : emptyTest){
        ASSERT_EQ(key, NULL);
    }

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    int order[] = {8, 15, 20, 25, 28, 30, 40, 50, 60, 70};
    for (int i = 0; i < n; i++)
        intTest.put(arr[i], arr[i]);

    int j = 0;
    for(auto key : intTest)
        EXPECT_EQ(key, order[j++]);


    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    string order2[] = {"edward", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    j = 0;
    for(auto key : mixDupTest)
        EXPECT_EQ(key, order2[j++]);


    mymap<double, bool> mixDupTest2;
    n = 10;
    double arr2[] = {30.5, 15, 50.5, 15, 25, 70, 15, 28, 50.5, 60.5};
    bool arr3[] = {true, false, true, true, false, false, true, false, true, true};
    double order3[] = {15, 25, 28, 30.5, 50.5, 60.5, 70};
    for (int i = 0; i < n; i++)
        mixDupTest2.put(arr2[i], arr3[i]);
    j = 0;
    for(auto key : mixDupTest2)
        EXPECT_EQ(key, order3[j++]);

}

// tests clear function
TEST(mymap, clear){
    mymap<char, bool> emptyTest;
    ASSERT_EQ(emptyTest.Size(), 0);
    emptyTest.clear();
    ASSERT_EQ(emptyTest.Size(), 0);

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};

    for (int i = 0; i < n; i++){
        EXPECT_EQ(intTest.Size(), i);
        intTest.put(arr[i], arr[i]);
    }
    ASSERT_EQ(intTest.Size(), n);
    intTest.clear();
    ASSERT_EQ(intTest.Size(), 0);

    mymap<string, double> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    double arr5[] = {3.5, 6, 10, 15.9, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);

    ASSERT_EQ(mixDupTest.Size(), 3);
    mixDupTest.clear();
    ASSERT_EQ(mixDupTest.Size(), 0);

    mymap<int, int> largeRandTest;
    int calcSize = 0;
    for(int i = 0; i < 100; i++){
        int randKey = rand()%1000;
        if(largeRandTest.contains(randKey)){
            largeRandTest.put(randKey, rand() % 1000);
        }
        else{
            largeRandTest.put(randKey, rand() % 1000);
            calcSize++;
        }
    }
    ASSERT_EQ(largeRandTest.Size(), calcSize);
    largeRandTest.clear();
    ASSERT_EQ(largeRandTest.Size(), 0);
}

// tests the equal operator (=)
TEST(mymap, equal_operator) {
    mymap<int, int> emptyTest;
    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++)
        intTest.put(arr[i], arr[i]);
    ASSERT_EQ(emptyTest.Size(), 0);
    ASSERT_EQ(intTest.Size(), n);
    emptyTest = intTest;
    ASSERT_EQ(emptyTest.Size(), n);
    ASSERT_EQ(intTest.Size(), n);
    ASSERT_EQ(emptyTest.toString(), intTest.toString());

    mymap<char, double> test1;
    mymap<char, double> test2;
    test1.put('a', 99.0);
    test1.put('g', 89.3);
    test1.put('d', 39.1);
    test2.put('w', 72.3);
    test2.put('p', 58.0);
    test1 = test2;
    ASSERT_EQ(test1.toString(), test2.toString());
    test2 = test1;
    ASSERT_EQ(test2.toString(), test1.toString());

    mymap<char, int> rand1;
    mymap<char, int> rand2;
    for(int i = 0; i < 50; i++){
        rand1.put(rand() % 26, rand() % 100);
    }
    rand2 = rand1;
    ASSERT_EQ(rand1.Size(), rand2.Size());
    ASSERT_EQ(rand1.toString(), rand2.toString());
}

// tests the copy constructor
TEST(mymap, copy_constructor){
    mymap<char, char> empty1;
    mymap<char, char> empty2 = empty1;
    ASSERT_EQ(empty1.Size(), 0);
    ASSERT_EQ(empty2.Size(), 0);
    ASSERT_EQ(empty1.toString(), empty2.toString());

    mymap<int, int> intTest;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++)
        intTest.put(arr[i], arr[i]);
    mymap<int, int> cmpTest = intTest;
    ASSERT_EQ(cmpTest.Size(), n);
    ASSERT_EQ(intTest.Size(), n);
    ASSERT_EQ(cmpTest.toString(), intTest.toString());

    mymap<char, int> rand1;
    for(int i = 0; i < 50; i++){
        rand1.put(rand() % 26, rand() % 100);
    }
    mymap<char, int> rand2 = rand1;
    ASSERT_EQ(rand1.Size(), rand2.Size());
    ASSERT_EQ(rand1.toString(), rand2.toString());
}

// tests checkbalance function
TEST(mymap, checkBalance){
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for(int i = 0; i < 3; i++)
        map.put(arr[i], arr[i]);
    string test = "key: 2, nL: 1, nR: 1\n"
                  "key: 1, nL: 0, nR: 0\n"
                  "key: 3, nL: 0, nR: 0\n";
    ASSERT_EQ(map.checkBalance(), test);

    mymap<int, int> intTest;
    int n = 10;
    int arr2[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++)
        intTest.put(arr2[i], arr2[i]);
    string test2 = "key: 30, nL: 5, nR: 4\n"
                   "key: 15, nL: 1, nR: 3\n"
                   "key: 8, nL: 0, nR: 0\n"
                   "key: 25, nL: 1, nR: 1\n"
                   "key: 20, nL: 0, nR: 0\n"
                   "key: 28, nL: 0, nR: 0\n"
                   "key: 50, nL: 1, nR: 2\n"
                   "key: 40, nL: 0, nR: 0\n"
                   "key: 70, nL: 1, nR: 0\n"
                   "key: 60, nL: 0, nR: 0\n";
    ASSERT_EQ(intTest.checkBalance(), test2);

    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    string test3 = "key: strach, nL: 1, nR: 1\n"
                   "key: edward, nL: 0, nR: 0\n"
                   "key: tyler, nL: 0, nR: 0\n";
    ASSERT_EQ(mixDupTest.checkBalance(),test3);

    mymap<double, bool> mixTest;
    n = 10;
    double arr6[] = {30.5, 15, 50.5, 8.5, 25, 70, 20.5, 28, 40.5, 60.5};
    bool arr7[] = {true, false, true, true, false, false, true, false, true, true};
    for (int i = 0; i < n; i++)
        mixTest.put(arr6[i], arr7[i]);
    string test4 = "key: 30.5, nL: 5, nR: 4\n"
                   "key: 15, nL: 1, nR: 3\n"
                   "key: 8.5, nL: 0, nR: 0\n"
                   "key: 25, nL: 1, nR: 1\n"
                   "key: 20.5, nL: 0, nR: 0\n"
                   "key: 28, nL: 0, nR: 0\n"
                   "key: 50.5, nL: 1, nR: 2\n"
                   "key: 40.5, nL: 0, nR: 0\n"
                   "key: 70, nL: 1, nR: 0\n"
                   "key: 60.5, nL: 0, nR: 0\n";
    ASSERT_EQ(mixTest.checkBalance(), test4);
}

// tests toVector function
TEST(mymap, toVector){
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for(int i = 0; i < 3; i++)
        map.put(arr[i], arr[i]);
    vector< pair<int, int> > test1 = { {1, 1}, {2, 2}, {3, 3}};
    vector< pair<int, int> > pairs1 = map.toVector();
    ASSERT_EQ(pairs1, test1);

    mymap<int, int> intTest;
    int n = 10;
    int arr2[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++)
        intTest.put(arr2[i], arr2[i]);
    vector< pair<int, int> > test2 = { {8, 8}, {15, 15}, {20, 20}, {25, 25}, {28, 28},
                                       {30, 30}, {40, 40}, {50, 50}, {60, 60}, {70, 70}};
    vector< pair<int, int> > pairs2 = intTest.toVector();
    ASSERT_EQ(pairs2, test2);

    mymap<string, int> mixDupTest;
    n = 5;
    string arr4[] = {"tyler", "edward", "strach", "strach", "tyler"};
    int arr5[] = {3, 6, 10, 15, 20};
    for (int i = 0; i < n; i++)
        mixDupTest.put(arr4[i], arr5[i]);
    vector< pair<string, int> > test3 = {{"edward", 6}, {"strach", 15}, {"tyler", 20}};
    vector< pair<string, int> > pairs3 = mixDupTest.toVector();
    ASSERT_EQ(pairs3, test3);
}
