# geosketchpad-native

```shell
emcmake cmake -B build -S.
```


1：1真实感地理画板
地理画板（geosketchpad）旨在结合传统的渲染管线、先进的AIGC管线完成地理全空间要素渲染。
全空间要素概念：
- 地、海、空、天包含的要素均为全空间概念包括的内容
- 地理画板主要将人类主要活动区域，即中观尺度的地理要素（米）级进行物理材质描述精细展示；包括
- - 基于PBR理论的物理材质表达
- - 地质的表达
- - 基于AIGC的孪生建模 + 渲染
- 海、空、天 宏观尺度以仿真计算为主，尽可能完成
- - 水渲染，包括流动、淹没等。（海，地）
- - 自然效应如丁达尔、锐利散射、云层、天气等（空）
- - 大气层

# tool #
> 
``` shell
set http_proxy=http://127.0.0.1:1080
set https_proxy=http://127.0.0.1:1080
git submodule add https://github.com/g-truc/glm.git third_party/glm
```

## maestro ##
核心数字资产处理模块

## ccs ###
Camera Control System, 运镜系统


