mergeInto(LibraryManager.library, {
  console_log: function (ptr) {
    console.log(UTF8ToString(ptr));
  },
  alert: function (ptr) {
    alert(UTF8ToString(ptr));
  },
  goto_link: function (ptr) {
    window.location.href = UTF8ToString(ptr);
  },
  open_link: function (ptr) {
    window.open(UTF8ToString(ptr), "_blank");
  },
});
