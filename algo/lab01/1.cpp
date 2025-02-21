#include <iostream>
#include <vector>

// 分治法求偶数个数的递归函数
int countEven(const std::vector<int>& arr, int left, int right) {
    // 递归的基准情况：如果子集合只有一个元素
    if (left == right) {
        return arr[left] % 2 == 0 ? 1 : 0;
    }

    // 计算中间位置
    int mid = (left + right) / 2;

    // 递归计算左右两部分的偶数个数
    int leftCount = countEven(arr, left, mid);
    int rightCount = countEven(arr, mid + 1, right);

    // 合并结果
    return leftCount + rightCount;
}

int main() {
    // 测试数据
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 调用分治法计算偶数个数
    int result = countEven(arr, 0, arr.size() - 1);

    std::cout << "偶数元素的数量是: " << result << std::endl;

    return 0;
}
