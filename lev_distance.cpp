#include <mysql.h>

//@func:求三个数的最小值
unsigned min(unsigned x,unsigned y,unsigned z )
{
    unsigned tmp=(x<y ? x:y);
    tmp=(tmp<z ? tmp:z);
    return tmp;
}


//@func:计算字符串s 和 t之间的levenshtein距离
//@paras:s和t均为c风格字符串
unsigned lev_distance(const char * s,const char *t)
{
    //n:目标单词t的长度   m:源单词s的长度
    unsigned m_tmp=0,n_tmp=0;
    int i=0;
    //计算源单词长度
    while(s[i])
    {
        i++;
        m_tmp++;
    }
    //计算目标单词长度
    i=0;
    while(t[i])
    {
        i++;
        n_tmp++;
    }
    if(m_tmp==0)
        return n_tmp;
    if(n_tmp==0)
        return m_tmp;

    const unsigned m=m_tmp+1;
    const unsigned n=n_tmp+1;
    unsigned matrix[m][n];
    //给矩阵的第0行和第0列赋值
    for(i=0;i<m;i++)
        matrix[i][0]=i;
    for(i=0;i<n;i++)
        matrix[0][i]=i;
    //填充矩阵的其他元素，逐行填充
    int j;
    for(i=1;i<m;i++)
        for(j=1;j<n;j++)
        {
            unsigned cost=1;
            if(s[i-1]==t[j-1])
                cost=0;
            matrix[i][j]=min(matrix[i-1][j]+1,matrix[i][j-1]+1,matrix[i-1][j-1]+cost);
        }
    //返回matrix[m-1][n-1],即两个字符串之间的距离
    return matrix[m-1][n-1];
}



extern "C" unsigned levenshtein(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	unsigned dis = lev_distance(args->args[0],args->args[1]);
    return dis;
}

extern "C" my_bool levenshtein_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
    return 0;
}
