# sqldb
一个小型的数据库引擎

### V1.0
**1.  底层数据结构**
* **DBList**（双端链表）
 ![avatar](http://39.107.83.159/static/update_images/5-03_01.png)
* **DBMap**（哈希表）**rehash**决定是否重新哈希(当**used/size>0.75**时)，平常只有**ht**在使用，只有当重新哈希时才会用到**ht_temp**，当发生冲突时由**next指针**连接所有冲突**HashEntry**
![avatar](http://39.107.83.159/static/update_images/5-03_00.png)


**2. Command**
 * 操作字符串命令
  ![avatar](http://39.107.83.159/static/update_images/sqldb_5_03_02.png)
 * 操作链表命令
  ![avatar](http://39.107.83.159/static/update_images/sqldb_5_03_03.png)
 * 操作哈希表命令
  ![avatar](http://39.107.83.159/static/update_images/sqldb_5_03_04.png)
 * 各种删除命令
  ![avatar](http://39.107.83.159/static/update_images/sqldb_5_03_05.png)
 * 其他命令
  ![avatar](http://39.107.83.159/static/update_images/sqldb_5_03_06.png)
