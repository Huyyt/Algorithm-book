二分图:
最大匹配:二分图中每条边的权值都相同 求边的最大值 可转化为最大流.
最优匹配:带权“最大匹配”  如果个数不相等,可以通过补点加0边实现转化 利用KM算法实现.
最小点覆盖:选最少的点使得二分图中每一条边的两个顶点中至少有一个点被选中 最小点覆盖数等于最大匹配数
最小点权覆盖=总权值-最大点权独立集
最小路径覆盖:DAG中 用尽量少的链把每个点包括进去 答案为|V|-最大匹配数
最大独立集:寻找一个点集,使得其中任意两点在图中无对应边.如果在一般图中是NP问题 但在二分图中 答案为|V|-最大匹配数
最小边覆盖:选最少的边使得图内的每一个点都在选中的某一条边上 最小边覆盖等于最大独立集

网络流图
最大权闭合子图
有向图,每个点有点权(正/负),要选择一个点的话就要选它的所有后继节点.问能得到的最大权值为多少
建图:A[i]>0 则add(S,i,A[i]) A[i]<则add(i,T,-A[i]) 答案为正权值之和-最大流.
