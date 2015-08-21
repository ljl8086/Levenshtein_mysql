#### Levenshtein_mysql
###1、功能描述:

mysql 自定义函数。用来计算字符A转换成字符串B所花费的代价，数值越小，代价越低。（换句话来说，就计算两个字符串的相似度，值越小相似度越高）。

该实现采用了编辑距离算法，详见：http://baike.baidu.com/link?url=EhmqDIoInSurOWI8VfR5bdmwxuYjPGKgqET2oNyv9--zDREhTUe5sYdxWLxS4v3tdK1PJVOFaOy9c6uHoElBSK

###2、使用方法：

  使用源代码的话，从第1步开始。如果是直接使用二进制发布包的话，直接从第4步开始即可。

  1）下载本代码

  2）安装mysql开发包。

      mysql主分支文件名类型：libmysqlclient15-dev
      mariaDB分支文件类似：MariaDB-10.0.21-centos7-x86_64-devel

  3）编译源代码：

      g++ -shared -fPIC -I /usr/include/mysql -o lev_distance.so lev_distance.cpp 

  4）将so文件复制到mysql插件目录

      cp lev_distance.so /usr/lib64/mysql/plugin

  5）创建mysql自义函数。

      CREATE FUNCTION levenshtein RETURNS INTEGER SONAME 'lev_distance.so';

  6）完成。
  
  7）测试：

      SELECT levenshtein('abc','dbca')
      

