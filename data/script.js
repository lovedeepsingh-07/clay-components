mergeInto(LibraryManager.library, {
  console_log: function (ptr) {
    console.log(UTF8ToString(ptr));
  },
  alert: function (ptr) {
    alert(UTF8ToString(ptr));
  },
});
