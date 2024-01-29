#include <pgmspace.h>

const char errorpassword[] PROGMEM = R"rawliteral(
<style>
/* 基础样式 */
body {
    font-family: Arial, sans-serif; /* 使用 Arial 字体 */
    text-align: center; /* 文本居中 */
    margin-top: 20%; /* 上边距为页面高度的 20% */
    font-size: 33px; /* 字体大小为 20 像素 */
}
/* 在小屏幕下的样式调整 */
@media only screen and (max-width: 600px) {
    body {
        margin-top: 10%; /* 上边距调整为页面高度的 10% */
        font-size: 20px; /* 字体大小调整为 16 像素 */
    }
}
/* 按钮样式 */
.button-style {
    font-size: 43px;
    text-decoration: none; /* 去除下划线 */
    width: 280px;
    height: 120px;
    background-color: #007bff; /* 背景色为蓝色 */
    color: #fff; /* 文字颜色为白色 */
    padding: 10px 20px; /* 内边距 */
    border-radius: 5px; /* 圆角 */
    display: inline-block; /* 内联块元素 */
    border: none; /* 去除边框 */
    cursor: pointer; /* 鼠标指针样式为手型 */
}
</style>
<body>
    <p>连接失败，请检查您的网络和密码。</p>
    <p>Connection failed. Please check your network and password.</p>
    <p style='margin-top: 20px;'>
    <!-- 返回按钮 -->
    <button onclick='window.location.href=\"/\"' class='button-style'>返回</button>
    </p>
</body>

)rawliteral";