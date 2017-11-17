



本demo使用了官方SDK中自带的demo作为基础,然后参考了别人的教程,然后 debug debug debug 而成

### 编译需求:
1. Photoshop CC 2017
1. [Photoshop CC 2017 SDK](http://www.adobe.com/devnet/photoshop/sdk.html)
1. VS 2015

### 安装方式:
编译之后将`Output`目录下的`8bf`文件复制到`Photoshop`安装目录下的`Plug-ins`文件夹下

(在我的电脑上对应目录为`C:\Program Files\Adobe\Adobe Photoshop CC 2017\Plug-ins\`)

重启Ps之后,在顶部菜单里就可以看到  `滤镜>AdobeSDK>ColorMunger` 选项

### 操作像素
在`DoContinue`里操作像素,可以取出RGBA进去需要的处理.
此处是把灰度低于180的像素点直接给删除(调成透明的)

```c
float gray = ( 299*r +  587*g + 114*b + 500) / 1000;
uint8 p = 60;
if(gray<180){
    //pDataOut[indexOut] = 0;//Red  
    //pDataOut[indexOut + 1] = 0;//Green 
    //pDataOut[indexOut + 2] = 0;//Blue
    pDataOut[indexOut + 3] = 255;
}
else {
    pDataOut[indexOut] = 255;//Red  
    pDataOut[indexOut + 1] = 0;//Green 
    pDataOut[indexOut + 2] = 0;//Blue
    pDataOut[indexOut + 3] = 0;
}

```


### 相关参考链接:
1. [对Photoshop第三方滤镜插件开发的简介](http://www.cnblogs.com/hoodlum1980/archive/2008/02/28/1085158.html)
1. [Adobe CEP 开发](http://www.cnblogs.com/hoodlum1980/archive/2008/02/28/1085158.html)


