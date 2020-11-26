# Generated by Selenium IDE
import pytest
import time
import json
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

class TestDraw():
  def setup_method(self, method):
    self.driver = webdriver.Chrome()
    self.vars = {}
  
  def teardown_method(self, method):
    self.driver.quit()
  
  def test_draw(self):
    # Test name: draw
    # Step # | name | target | value
    # 1 | open | / | 
    self.driver.get("http://app.xunjietupian.com/")
    # 2 | setWindowSize | 1552x840 | 
    self.driver.set_window_size(1552, 840)
    # 3 | click | css=.raw:nth-child(1) > a:nth-child(7) img | 
    self.driver.find_element(By.CSS_SELECTOR, ".raw:nth-child(1) > a:nth-child(7) img").click()
    # 4 | click | css=.btn-first-load | 
    # self.driver.find_element(By.CSS_SELECTOR, ".btn-first-load").click()
    # 5 | type | css=.tui-image-editor-load-btn | /
    # self.driver.find_element(By.CSS_SELECTOR, ".tui-image-editor-load-btn").send_keys("/")
    upload = self.driver.find_element(By.CSS_SELECTOR, ".tui-image-editor-load-btn")
    time.sleep(1)
    upload.send_keys("E:/code/PycharmProjects/Test2/img/test.jpg")
    time.sleep(1)
    # 6 | mouseDownAt | css=.upper-canvas | 338.3999938964844,22.399993896484375
    element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    actions = ActionChains(self.driver)
    actions.move_to_element(element).move_by_offset(-200,-200).click_and_hold().move_by_offset(-100,-100).release().perform()
    # 7 | mouseMoveAt | css=.upper-canvas | 338.3999938964844,22.399993896484375
    # element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    # actions = ActionChains(self.driver)
    # actions.move_to_element(element).perform()
    # 8 | mouseUpAt | css=.upper-canvas | 338.3999938964844,22.399993896484375
    # element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    # actions = ActionChains(self.driver)
    # actions.move_to_element(element).release().perform()
    # 9 | click | css=.upper-canvas | 
    self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas").click()
    # 10 | click | css=.color-picker-draw > .fl:nth-child(1) | 
    self.driver.find_element(By.CSS_SELECTOR, ".color-picker-draw > .fl:nth-child(1)").click()
    # 11 | mouseDownAt | css=.upper-canvas | 391.3999938964844,71.39999389648438
    element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    actions = ActionChains(self.driver)
    actions.move_to_element(element).click_and_hold().move_by_offset(-100,100).release().perform()
    # 12 | mouseMoveAt | css=.upper-canvas | 391.3999938964844,71.39999389648438
    # element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    # actions = ActionChains(self.driver)
    # actions.move_to_element(element).perform()
    # 13 | mouseUpAt | css=.upper-canvas | 391.3999938964844,71.39999389648438
    # element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    # actions = ActionChains(self.driver)
    # actions.move_to_element(element).release().perform()
    # 14 | click | css=.upper-canvas | 
    self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas").click()
    # 15 | type | css=.range-brush-width | 18
    self.driver.find_element(By.CSS_SELECTOR, ".range-brush-width").send_keys("18")
    # 16 | click | css=.range-brush-width | 
    self.driver.find_element(By.CSS_SELECTOR, ".range-brush-width").click()
    # 17 | click | css=.color-picker-draw > .fl:nth-child(6) | 
    self.driver.find_element(By.CSS_SELECTOR, ".color-picker-draw > .fl:nth-child(6)").click()
    # 18 | type | css=.range-brush-opacity | 73
    self.driver.find_element(By.CSS_SELECTOR, ".range-brush-opacity").send_keys("73")
    # 19 | click | css=.range-brush-opacity | 
    self.driver.find_element(By.CSS_SELECTOR, ".range-brush-opacity").click()
    # 20 | mouseDownAt | css=.upper-canvas | 699.3999938964844,268.3999938964844
    element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    actions = ActionChains(self.driver)
    actions.move_to_element(element).move_by_offset(1,1).click_and_hold().move_by_offset(100,-100).release().perform()
    # 21 | mouseMoveAt | css=.upper-canvas | 699.3999938964844,268.3999938964844
    # element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    # actions = ActionChains(self.driver)
    # actions.move_to_element(element).perform()
    # 22 | mouseUpAt | css=.upper-canvas | 699.3999938964844,268.3999938964844
    # element = self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas")
    # actions = ActionChains(self.driver)
    # actions.move_to_element(element).release().perform()
    # 23 | click | css=.upper-canvas | 
    self.driver.find_element(By.CSS_SELECTOR, ".upper-canvas").click()
    # 24 | click | css=.btn-basic-undo > img | 
    self.driver.find_element(By.CSS_SELECTOR, ".btn-basic-undo > img").click()
    # 25 | click | css=.btn-basic-redo > img | 
    self.driver.find_element(By.CSS_SELECTOR, ".btn-basic-redo > img").click()
    # 26 | click | css=.btn-basic-reset > img | 
    self.driver.find_element(By.CSS_SELECTOR, ".btn-basic-reset > img").click()
    # 27 | click | css=.btn-basic-undo > img | 
    self.driver.find_element(By.CSS_SELECTOR, ".btn-basic-undo > img").click()
    # 28 | click | css=.btn-down-load | 
    self.driver.find_element(By.CSS_SELECTOR, ".btn-down-load").click()
    time.sleep(2)
    # 29 | close |  | 
    self.driver.close()
  
