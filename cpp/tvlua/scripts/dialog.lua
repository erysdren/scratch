local d = TDialog.new(TRect.new(25, 5, 55, 16), "Hello, World!")

d:insert(TStaticText.new(TRect.new(3, 5, 15, 6), "How are you?"));
d:insert(TButton.new(TRect.new(16, 2, 28, 4), "Terrific", tv.cm.Cancel, tv.bf.Normal));
d:insert(TButton.new(TRect.new(16, 4, 28, 6), "Ok", tv.cm.Cancel, tv.bf.Normal));
d:insert(TButton.new(TRect.new(16, 6, 28, 8), "Lousy", tv.cm.Cancel, tv.bf.Normal));
d:insert(TButton.new(TRect.new(16, 8, 28, 10), "Cancel", tv.cm.Cancel, tv.bf.Normal));
