package com.example.learnffmpeg.config

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.learnffmpeg.R

class FFmpegConfigInfoActivity : AppCompatActivity() {

    private var configInfoTv: TextView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_ffmpeg_config_info)
        configInfoTv = findViewById(R.id.config_info_tv)
        configInfoTv?.text = ConfigInfo.getConfigInfo()
    }

}