//index.js
//获取应用实例
var app = getApp();

Page({
  data: {
    projects: []
  },
  
  //事件处理函数
  // 导航到项目运行页面
  ProjectDetail: function(e) {
    var index = e.currentTarget.id;
    wx.navigateTo({
      url: '../detail/detail?index='+index
    });
  },
  DelItem: function(e) {
    var index = e.currentTarget.id.split("-")[1];
    app.RemoveProjects(index,1);
    this.setData({projects: app.projects});
  },

  // 导航到项目创建页面
  CreateProject: function() {
    wx.navigateTo({
      url: '../creator/creator?index=-1&mode=create'
    });
  },
  SettingAlarm: function() {
    wx.navigateTo({
      url: '../record/record'
    });
  },
  

  /** 生命周期处理函数 **/
  onLoad: function() {
    app.LoadProjects();
  },
  onShow: function() {
    this.setData({projects: app.projects});
  }
})
