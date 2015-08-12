<?php

/**
 * @file
 * The default format for Viet Nam adresses.
 */

$plugin = array(
  'title' => t('Address form (specific for Viet Nam)'),
  'format callback' => 'addressfield_vn_format_address_generate',
  'type' => 'address',
  'weight' => -100,
);

/**
 * Format callback for Viet Nam address.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_vn_format_address_generate(&$format, $address, $context = array()) {
  if ($address['country'] == 'VN') {
    unset($format['locality_block']['administrative_area']);
	unset($format['locality_block']['postal_code']);
	
    $format['locality_block']['locality'] = array(
      '#title' => t('City/Province'),
      '#options' => _addressfield_vn_city_list(),
      '#required' => TRUE,
      '#attributes' => array('class' => array('locality')),
      '#weight' => 1,
    );
    $format['locality_block']['dependent_locality'] = array(
      '#title' => t('District'),
      '#size' => 20,
      '#tag' => 'div',
      '#attributes' => array('class' => array('dependent', 'district')),
      '#weight' => 2,
    );
    $format['locality_block']['postal_code'] = array(
      '#title' => t('Postal code'),
      '#size' => 10,
      '#required' => FALSE,
      '#attributes' => array('class' => array('postal-code')),
      '#weight' => 3,
    );
    // Default district
    if ($address['locality'] == 8) {
      $format['locality_block']['dependent_locality']['#options'] = array(
        t('Quan 1'),
        t('Quan 2'),
        t('Quan 3'),
        t('Quan 4'),
        t('Quan 5'),
        t('Quan 6'),
        t('Quan 7'),
        t('Quan 8'),
        t('Quan 9'),
        t('Quan 10'),
        t('Quan 11'),
        t('Quan 12'),
        t('Go Vap'),
        t('Tan Binh'),
        t('Tan Phu'),
        t('Binh Thanh'),
        t('Phu Nhuan'),
        t('Thu Duc'),
        t('Binh Tan'),
        t('Cu Chi'),
        t('Hoc Mon'),
        t('Binh Chanh'),
        t('Nha Be'),
        t('Can Gio'),
      );
    } elseif ($address['locality'] == 4) {
      $format['locality_block']['dependent_locality']['#options'] = array(
        t('Ba Dinh'),
        t('Cau Giay'),
        t('Dong Da'),
        t('Hai Ba Trung'),
        t('Hoan Kiem'),
        t('Hoang Mai'),
        t('Long Bien'),
        t('Tay Ho'),
        t('Thanh Xuan'),
        t('Ha Dong'),
        t('Huyen Dong Anh'),
        t('Huyen Gia Lam'),
        t('Huyen Soc Son'),
        t('Huyen Thanh Tri'),
        t('Huyen Tu Liem'),
        t('Thi Xa Son Tay'),
        t('Huyen Ba Vi'),
        t('Huyen Chuong My'),
        t('Huyen Dan Phuong'),
        t('Huyen Hoai Duc'),
        t('Huyen My Duc'),
        t('Huyen Phu Xuyen'),
        t('Huyen Phuc Tho'),
        t('Huyen Quoc Oai'),
        t('Huyen Thach That'),
        t('Huyen Thanh Oai'),
        t('Huyen Thuong Tin'),
        t('Huyen Ung Hoa'),
        t('Huyen Me Linh'),
      );
    } elseif ($address['locality'] == 511) {
      $format['locality_block']['dependent_locality']['#options'] = array(
        t('Hai Chau'),
        t('Thanh Khe'),
        t('Son Tra'),
        t('Ngu Hanh Son'),
        t('Lien Chieu'),
        t('Cam Le'),
        t('Huyen Hoa Vang'),
        t('Huyen Dao Hoang Sa'),
      );
    } elseif ($address['locality'] == 31) {
      $format['locality_block']['dependent_locality']['#options'] = array(
        t('Duong Kinh'),
        t('Do Son'),
        t('Hai An'),
        t('Kien An'),
        t('Hong Bang'),
        t('Ngo Quyen'),
        t('Le Chan'),
        t('Huyen An Duong'),
        t('Huyen An Lao'),
        t('Huyen Dao Bach Long Vi'),
        t('Huyen Cat Hai'),
        t('Huyen Kien Thuy'),
        t('Huyen Tien Lang'),
        t('Huyen Vinh Bao'),
        t('Huyen Thuy Nguyen'),
      );
    } elseif ($address['locality'] == 710) {
      $format['locality_block']['dependent_locality']['#options'] = array(
        t('Ninh Kieu'),
        t('Binh Thuy'),
        t('Cai Rang'),
        t('O Mon'),
        t('Thot Not'),
        t('Huyen Phong Dien'),
        t('Huyen Co Do'),
        t('Huyen Thoi Lai'),
        t('Huyen Vinh Thanh'),
      );
    }
  }
  // Format render
  if ($context['mode'] == 'render') {
    $format['locality_block']['dependent_locality']['#weight'] = 1;
    $format['locality_block']['locality']['#weight'] = 2;
    $format['locality_block']['postal_code']['#weight'] = 3;
    $format['locality_block']['postal_code']['#prefix'] = ' ';
  }
  // Check ajax form in Viet Nam
  if ($context['mode'] == 'form' && $address['country'] == 'VN') {
    $format['locality_block']['locality']['#ajax'] = array(
      'callback' => 'addressfield_standard_widget_refresh',
      'wrapper' => $format['#wrapper_id'],
      'method' => 'replace',
    );
  } else {
    if (isset($format['locality_block']['locality'])) {
      $format['locality_block']['locality']['#ajax'] = array();
    }
  }
}

/**
 * The list city/province in Viet Nam.
 */
function _addressfield_vn_city_list() {
  // Using http://adslvnpt.com/dien-thoai-co-dinh-va-gphone/huong-dan-su-dung/bang-ma-vung
  $data = array(
    '' => t('--'),
    4 => t('Ha Noi'),
    8 => t('Ho Chi Minh'),
    511 => t('Da Nang'),
    31 => t('Hai Phong'),
    710 => t('Can Tho'),
    76 => t('An Giang'),
    64 => t('Ba Ria - Vung Tau'),
    781 => t('Bac Lieu'),
    240 => t('Bac Giang'),
    281 => t('Bac Can'),
    241 => t('Bac Ninh'),
    75 => t('Ben Tre'),
    650 => t('Binh Duong'),
    651 => t('Binh Phuoc'),
    62 => t('Binh Thuan'),
    780 => t('Ca Mau'),
    26 => t('Cao Bang'),
    500 => t('Dac Lac'),
    501 => t('Dac Nong'),
    230 => t('Dien Bien'),
    61 => t('Dong Nai'),
    67 => t('Dong Thap'),
    59 => t('Gia Lai'),
    219 => t('Ha Giang'),
    351 => t('Ha Nam'),
    39 => t('Ha Tinh'),
    320 => t('Hai Duong'),
    711 => t('Hau Giang'),
    218 => t('Hoa Binh'),
    321 => t('Hung Yen'),
    58 => t('Khanh Hoa'),
    77 => t('Kien Giang'),
    60 => t('Kon Tum'),
    231 => t('Lai Chau'),
    63 => t('Lam Dong'),
    25 => t('Lang Son'),
    20 => t('Lao Cai'),
    72 => t('Long An'),
    350 => t('Nam Dinh'),
    38 => t('Nghe An'),
    30 => t('ninh Binh'),
    68 => t('Ninh Thuan'),
    210 => t('Phu Tho'),
    57 => t('Phu Yen'),
    52 => t('Quang Binh'),
    510 => t('Quang Nam'),
    55 => t('Quang Ngai'),
    33 => t('Quang Ninh'),
    53 => t('Quang Tri'),
    79 => t('Soc Trang'),
    22 => t('Son La'),
    66 => t('Tay Ninh'),
    36 => t('Thai Binh'),
    280 => t('Thai Nguyen'),
    37 => t('Thanh Hoa'),
    54 => t('Thua Thien - Hue'),
    73 => t('Tien Giang'),
    74 => t('Tra Vinh'),
    27 => t('Tuyen Quang'),
    70 => t('Vinh Long'),
    211 => t('Vinh Phuc'),
    29 => t('Yen Bai')
  );

  return $data;
}
