// Copyright 2022 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package com.android.example;

import com.google.androidgamesdk.GameActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.MotionEvent;
import android.widget.*;
import android.util.DisplayMetrics;

public class MainActivity extends GameActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        this.createUI();
    }
    static {
        System.loadLibrary("vktuts");
    }

    private void createUI() {
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        int width = dm.widthPixels;
        int height = dm.heightPixels;

        createButton(0, "Q", 1300, 600);
        createButton(1, "W", 1500, 600);
        createButton(2, "E", 1700, 600);
        createButton(3, "A", 1300, 800);
        createButton(4, "S", 1500, 800);
        createButton(5, "D", 1700, 800);
    }

    private void createButton(int id, String text, int x, int y) {
        Button btn = new Button(this);
        btn.setId(id);
        btn.setText(text);
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(150, 150);
        params.leftMargin = x;
        params.topMargin = y;
        btn.setLayoutParams(params);

        btn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int id = v.getId();
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        nativeKeyDown(id);
                        return true;
                    case MotionEvent.ACTION_UP:
                        nativeKeyUp(id);
                        return true;
                }
                return false;
            }
        });

        View v = this.getWindow().getDecorView();
        FrameLayout contentParent = (FrameLayout)v.findViewById(android.R.id.content);
        contentParent.addView(btn);
    }

    public native void nativeKeyDown(int code);
    public native void nativeKeyUp(int code);
}

