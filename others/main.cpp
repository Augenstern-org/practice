

// 在某一群山中，有四个固定通信基站A、B、C、D，
// 彼此间能进行通信处理相关业务。这四个基站分别建立在四座山上，
// 离海平面的垂直距离均为2KM。四个基站恰好构成正方形结构，边长为√2KM。

// 现有一架无人机P与四个固定基站建立网络联系，提供空中通信。
// 在通信期间，无人机P只能在正方形对角线交点O的正上方3KM范围内垂直移动（不包括O点）。

// 现有另一架无人机Q，要对通信过程中的五条线路BC、CD、PD、PA、PB进行检修并采集数据。
// 无人机Q在执行线路检修之前，必须要提前在上述五条线路上分别选取一个检测点（不包括无人机P和固定基站的位置）。
// 五个检测点确定后，无人机Q从BC上的检测点出发，沿直线飞行，
// 依次经过CD、PD、PA、PB上的检测点，最后飞回到BC上的检测点，形成一个回路。

// 现有任务需求：
//     ·制定无人机Q的飞行路线，使得回路中的五条线段长度均尽可能相等。

// 请你根据问题的描述，研究如下四个问题：
// （1）	建立合适的数学模型和算法，解决上述任务需求。
// （2）	若存在多条满足任务需求的飞行路线，请给出总数量。
// （3）	我们将第（2）问中长度最短的飞行路线记为最优飞行路线，请给出其相关信息：
//              ·路线长度和路线数量，以及每条最优飞行路线中无人机P和五个检测点的位置。
// （4）	在实际应用过程中，一般还需考虑五个检测点是否在同一平面内。
//          请判断是否存在每边长度尽可能相等、五点共面且路线长度最短的最优飞行路线，若存在请给出具体的信息。



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <Windows.h>


constexpr int MAX_SOLUTIONS = 1000;

// 基站坐标
// 这里定义了一个结构体来表示三维点
// 这个抽象数据类型包含的信息是点的 x, y, z 坐标
struct Point3D {
    Point3D(double X = 0, double Y = 0, double Z = 0): x(X), y(Y), z(Z){}
    double x, y, z;
};

// 解的结构
// 这也是个对象，表示的是一个解
// 定义了一个结构体来表示解，包括参数和对应的点坐标、总长度等
struct Solution{
    Solution(double T1 = 0, double T2 = 0, double S3 = 0, double S4 = 0, double S5 = 0, double zQ = 0):
        t1(T1), t2(T2), s3(S3), s4(S4), s5(S5), zQ(zQ),
        objective(0), total_length(0),
        E1(), E2(), E3(), E4(), E5(), Q() {}
    ~Solution() =default;
    double t1, t2, s3, s4, s5, zQ;
    double objective;
    double total_length;
    Point3D E1, E2, E3, E4, E5, Q;
    // 这就是之前定义的点坐标
    // 分别是检测点E1到E5和无人机位置P
};

// 全局变量，存储基站坐标和解
// Point3D A, B, C, D;
Point3D A(-1, -1, 2.0);
Point3D B(1, -1, 2.0);
Point3D C(1, 1, 2.0);
Point3D D(-1, 1, 2.0);
Solution solutions[MAX_SOLUTIONS];
int solution_count = 0;

// 初始化基站坐标
// void init_base_stations() {
    
// }

// 计算给出的 p1、p2 两点距离
double distance(Point3D p1, Point3D p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

// 该函数接受三个浮点数
// 用来限制传入的第一个参数 x 的参数范围，防止越界
double clamp(double x, double min_val, double max_val) {
    // 限制下界
    if (x < min_val) return min_val;
    // 限制上界
    if (x > max_val) return max_val;
    return x;
}

// 计算检测点坐标
// 该函数接受参数 t1, t2, s3, s4, s5, zQ
// t1 等代表各个检测点在对应边上的比例位置
// 并计算出检测点 E1 到 E5 以及无人机位置 Q 的坐标
// E1 到 E5 都是 Point3D 类型，其成员在前文有定义
// 结果存储在传入的 Point3D 指针中
void compute_points(double t1, double t2, double s3, double s4, double s5, double zQ,
                   Point3D *E1, Point3D *E2, Point3D *E3, Point3D *E4, Point3D *E5, Point3D *Q) {
    // 限制参数范围
    t1 = clamp(t1, 0.001, 0.999);
    t2 = clamp(t2, 0.001, 0.999);
    s3 = clamp(s3, 0.001, 0.999);
    s4 = clamp(s4, 0.001, 0.999);
    s5 = clamp(s5, 0.001, 0.999);
    zQ = clamp(zQ, 2.001, 5.0);
    
    Q->x = 0.0; Q->y = 0.0; Q->z = zQ;
    
    // E1 在 BC 上
    // 在 B 点和 C 点连成的这条线上
    // 按照 t1 这个比例尺，算出 E1 点的 x, y, z  坐标位置
    E1->x = B.x + t1 * (C.x - B.x);
    E1->y = B.y + t1 * (C.y - B.y);
    E1->z = B.z + t1 * (C.z - B.z);
    
    // E2在CD上（同上）
    E2->x = C.x + t2 * (D.x - C.x);
    E2->y = C.y + t2 * (D.y - C.y);
    E2->z = C.z + t2 * (D.z - C.z);
    
    // E3在PD上（同上）
    E3->x = Q->x + s3 * (D.x - Q->x);
    E3->y = Q->y + s3 * (D.y - Q->y);
    E3->z = Q->z + s3 * (D.z - Q->z);
    
    // E4在PA上（同上）
    E4->x = Q->x + s4 * (A.x - Q->x);
    E4->y = Q->y + s4 * (A.y - Q->y);
    E4->z = Q->z + s4 * (A.z - Q->z);
    
    // E5在PB上（同上）
    E5->x = Q->x + s5 * (B.x - Q->x);
    E5->y = Q->y + s5 * (B.y - Q->y);
    E5->z = Q->z + s5 * (B.z - Q->z);
}

// 目标函数：最小化五边长度差异，也就是找到最规则的五边形
// 函数返回值是方差，表示五边长度的差异
// 五边总长度通过指针参数 total_len 返回
double objective_function(double t1, double t2, double s3, double s4, double s5, double zQ,
                         double *total_len) {
    Point3D E1, E2, E3, E4, E5, Q;
    compute_points(t1, t2, s3, s4, s5, zQ, &E1, &E2, &E3, &E4, &E5, &Q);
    
    // 计算各边长度
    double L1 = distance(E1, E2);
    double L2 = distance(E2, E3);
    double L3 = distance(E3, E4);
    double L4 = distance(E4, E5);
    double L5 = distance(E5, E1);
    
    // 计算平均长度
    double lengths[5] = {L1, L2, L3, L4, L5};
    double mean = (L1 + L2 + L3 + L4 + L5) / 5.0;
    
    // 计算方差
    // 方差越小 → 各边长度越接近 → 五边形越规则
    // 方差越大 → 边长差异越大 → 五边形越不规则
    double variance = 0.0;
    for (int i = 0; i < 5; ++i) {
        double diff = lengths[i] - mean;
        variance += diff * diff;
    }
    
    // 返回五边总长度
    *total_len = L1 + L2 + L3 + L4 + L5;
    // 返回方差
    return variance;
}

// 检查是否五点共面
int are_coplanar(Point3D E1, Point3D E2, Point3D E3, Point3D E4, Point3D E5) {
    // 使用前四点构造平面，检查第五点距离
    Point3D v1 = {E2.x - E1.x, E2.y - E1.y, E2.z - E1.z};
    Point3D v2 = {E3.x - E1.x, E3.y - E1.y, E3.z - E1.z};
    
    // 计算法向量
    Point3D normal = {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
    
    // 计算E5到平面的距离
    Point3D v3 = {E5.x - E1.x, E5.y - E1.y, E5.z - E1.z};
    double dot_product = normal.x * v3.x + normal.y * v3.y + normal.z * v3.z;
    double distance = fabs(dot_product) / sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    
    return distance < 1e-6;
}

// 模拟退火算法
// 退火算法就像是在冶金中退火工艺：
//      ·高温时金属原子可以自由移动，
//      ·随着温度降低逐渐找到最稳定的晶体结构
Solution simulated_annealing() {
    // 初始参数
    // 其实就是随机捏一个五边形的形状
    // t1,t2控制边点位置，s3-s5控制其他边比例，zQ控制高度
    double t1 = 0.5, t2 = 0.5, s3 = 0.5, s4 = 0.5, s5 = 0.5, zQ = 2.0;
    double current_obj, new_obj, total_len;
    
    current_obj = objective_function(t1, t2, s3, s4, s5, zQ, &total_len);
    
    // 退火参数，包括初始温度、降温速率和迭代次数
    double temperature = 1.0;
    double cooling_rate = 0.95;
    int iterations = 1000;
    
    Solution best_solution;
    best_solution.objective = current_obj;
    best_solution.t1 = t1; best_solution.t2 = t2;
    best_solution.s3 = s3; best_solution.s4 = s4; best_solution.s5 = s5;
    best_solution.zQ = zQ;
    best_solution.total_length = total_len;
    
    // 随机数种子，根据时间生成，确保每次运行结果不同
    srand(time(NULL));
    
    for (int i = 0; i < iterations; ++i) {
        // 生成新解
        // 在当前位置附近随机微调参数，产生一个新的五边形形状
        // 这个随机数就是利用前文用时间生成的随机数种子生成的
        double new_t1 = t1 + (rand() / (double)RAND_MAX - 0.5) * 0.1;
        double new_t2 = t2 + (rand() / (double)RAND_MAX - 0.5) * 0.1;
        double new_s3 = s3 + (rand() / (double)RAND_MAX - 0.5) * 0.1;
        double new_s4 = s4 + (rand() / (double)RAND_MAX - 0.5) * 0.1;
        double new_s5 = s5 + (rand() / (double)RAND_MAX - 0.5) * 0.1;
        double new_zQ = zQ + (rand() / (double)RAND_MAX - 0.5) * 1;
        
        // 用之前的目标函数计算新五边形的"规则度得分"（方差）
        new_obj = objective_function(new_t1, new_t2, new_s3, new_s4, new_s5, new_zQ, &total_len);
        
        // 接受新解的概率
        double acceptance_probability = 0.0;
        // 如果新解更优，则直接接受
        if (new_obj < current_obj) {
            acceptance_probability = 1.0;
        } 
        // 新形状稍差，但以一定概率接受（温度高时概率大）
        // 高温时更容易接受较差解，帮助跳出局部最优
        // 低温时更倾向于接受更优解，收敛到全局最优
        else {
            acceptance_probability = exp(-(new_obj - current_obj) / temperature);
        }
        
        // 根据接受概率决定是否接受新解
        if (rand() / (double)RAND_MAX < acceptance_probability) {
            t1 = new_t1; t2 = new_t2; s3 = new_s3; s4 = new_s4; s5 = new_s5; zQ = new_zQ;
            current_obj = new_obj;
            
            // 更新历史最佳解 - 记住找到过的最好形状
            if (new_obj < best_solution.objective) {
                best_solution.objective = new_obj;
                best_solution.t1 = new_t1; best_solution.t2 = new_t2;
                best_solution.s3 = new_s3; best_solution.s4 = new_s4; best_solution.s5 = new_s5;
                best_solution.zQ = new_zQ;
                best_solution.total_length = total_len;
            }
        }
        
        // 降温
        // 每次循环后温度降低，搜索越来越"保守"。
        temperature *= cooling_rate;
    }
    
    // 计算最终的点坐标
    compute_points(best_solution.t1, best_solution.t2, best_solution.s3, 
                  best_solution.s4, best_solution.s5, best_solution.zQ,
                  &best_solution.E1, &best_solution.E2, &best_solution.E3,
                  &best_solution.E4, &best_solution.E5, &best_solution.Q);
    
    // 返回最优解
    return best_solution;
}

// 检查解是否重复
int is_duplicate_solution(Solution new_sol) {
    for (int i = 0; i < solution_count; ++i) {
        if (fabs(new_sol.t1 - solutions[i].t1) < 0.01 &&
            fabs(new_sol.t2 - solutions[i].t2) < 0.01 &&
            fabs(new_sol.s3 - solutions[i].s3) < 0.01 &&
            fabs(new_sol.s4 - solutions[i].s4) < 0.01 &&
            fabs(new_sol.s5 - solutions[i].s5) < 0.01 &&
            fabs(new_sol.zQ - solutions[i].zQ) < 0.1) {
            return 1;
        }
    }
    return 0;
}

// 寻找多个解
void find_multiple_solutions() {
    printf("寻找多个满足条件的解...\n");
    
    // 遍历多次模拟退火，寻找多个不同解
    for (int i = 0; i < 50 && solution_count < MAX_SOLUTIONS; ++i) {
        Solution sol = simulated_annealing();
        
        // 只保存目标函数值小于 1*10^(-3) 且不重复的解
        if (sol.objective < 1e-3 && !is_duplicate_solution(sol)) {
            solutions[solution_count++] = sol;
            printf("找到解 %d: obj=%.6f, 总长=%.6f\n", 
                   solution_count, sol.objective, sol.total_length);
        }
    }
    
    printf("共找到 %d 个满足条件的解\n", solution_count);
}

// 寻找最短路线
void find_shortest_route() {
    if (solution_count == 0) {
        printf("没有找到满足条件的解\n");
        return;
    }
    
    int best_index = 0;
    double min_length = solutions[0].total_length;
    
    // 在所有解中找到总长度最短的解
    // 函数没有传递参数是因为 solutions 和 solution_count 是全局变量
    for (int i = 1; i < solution_count; ++i) {
        if (solutions[i].total_length < min_length) {
            min_length = solutions[i].total_length;
            best_index = i;
        }
    }
    
    Solution best = solutions[best_index];
    printf("\n=== 最优飞行路线 ===\n");
    printf("总长度: %.6f km\n", best.total_length);
    printf("目标函数值: %.6f\n", best.objective);
    printf("参数: t1=%.4f, t2=%.4f, s3=%.4f, s4=%.4f, s5=%.4f, zQ=%.4f\n",
           best.t1, best.t2, best.s3, best.s4, best.s5, best.zQ);
    
    printf("\n无人机Q位置: (%.4f, %.4f, %.4f)\n", best.Q.x, best.Q.y, best.Q.z);
    printf("检测点E1: (%.4f, %.4f, %.4f)\n", best.E1.x, best.E1.y, best.E1.z);
    printf("检测点E2: (%.4f, %.4f, %.4f)\n", best.E2.x, best.E2.y, best.E2.z);
    printf("检测点E3: (%.4f, %.4f, %.4f)\n", best.E3.x, best.E3.y, best.E3.z);
    printf("检测点E4: (%.4f, %.4f, %.4f)\n", best.E4.x, best.E4.y, best.E4.z);
    printf("检测点E5: (%.4f, %.4f, %.4f)\n", best.E5.x, best.E5.y, best.E5.z);
    
    // 计算各边长度
    double L1 = distance(best.E1, best.E2);
    double L2 = distance(best.E2, best.E3);
    double L3 = distance(best.E3, best.E4);
    double L4 = distance(best.E4, best.E5);
    double L5 = distance(best.E5, best.E1);
    
    printf("\n各边长度:\n");
    printf("L1: %.6f\n", L1);
    printf("L2: %.6f\n", L2);
    printf("L3: %.6f\n", L3);
    printf("L4: %.6f\n", L4);
    printf("L5: %.6f\n", L5);
    
    // 计算平均长度和方差
    double mean = (L1 + L2 + L3 + L4 + L5) / 5.0;
    double variance = 0.0;
    variance += (L1-mean)*(L1-mean) + (L2-mean)*(L2-mean) + 
                (L3-mean)*(L3-mean) + (L4-mean)*(L4-mean) + (L5-mean)*(L5-mean);
    
    printf("平均长度: %.6f\n", mean);
    printf("方差: %.6f\n", variance);
}

// 检查共面解
void check_coplanar_solutions() {
    printf("\n=== 检查共面解 ===\n");
    int coplanar_count = 0;
    
    for (int i = 0; i < solution_count; ++i) {
        if (are_coplanar(solutions[i].E1, solutions[i].E2, solutions[i].E3, 
                        solutions[i].E4, solutions[i].E5)) {
            coplanar_count++;
            printf("解 %d 是共面的，总长度=%.6f\n", i+1, solutions[i].total_length);
        }
    }
    
    if (coplanar_count > 0) {
        printf("存在 %d 个共面最优飞行路线\n", coplanar_count);
    } else {
        printf("不存在满足条件的共面最优飞行路线\n");
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("=== 无人机检修路径优化问题 ===\n");
    printf("使用模拟退火算法求解\n\n");
    
    // init_base_stations();
    
    // 问题(1)(2)：寻找多个解
    find_multiple_solutions();
    
    // 问题(3)：寻找最短路线
    find_shortest_route();
    
    // 问题(4)：检查共面解
    check_coplanar_solutions();
    
    return 0;
}
