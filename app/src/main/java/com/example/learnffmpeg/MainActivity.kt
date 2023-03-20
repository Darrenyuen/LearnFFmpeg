package com.example.learnffmpeg

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import com.example.learnffmpeg.config.FFmpegConfigInfoActivity

class MainActivity : AppCompatActivity() {

    private var showConfigBtn: Button? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        showConfigBtn = findViewById(R.id.show_config_btn)
        showConfigBtn?.setOnClickListener {
            val intent = Intent(this, FFmpegConfigInfoActivity::class.java)
            startActivity(intent)
        }
    }
}