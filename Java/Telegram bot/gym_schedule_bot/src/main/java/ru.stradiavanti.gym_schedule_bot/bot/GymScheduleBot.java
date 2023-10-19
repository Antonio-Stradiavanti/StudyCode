package ru.stradiavanti.gym_schedule_bot.bot;

import org.telegram.telegrambots.bots.TelegramLongPollingBot;

public class GymScheduleBot extends TelegramLongPollingBot {
  // Переопределим конструктор

  public GymScheduleBot(String botToken) {
    super(botToken);
  }
}
