import React from 'react';
import GraphBody from '../../common/Graph/GraphBody';
import PropTypes from 'prop-types';
import { connect } from 'react-redux';
import styles from './Histogram.scss'

const Histogram = ({
  data,
  height,
  width,
}) => (
      <svg width={width} height={width}>
        <GraphBody
          UseLinearGradient={false}
          color={'blue'}
          points={data}
          x={0}
          y={600}
          fill={"blue"}
          fillOpacity={".5"}
          strokeWidth={1}
        />
        </svg>
);
Histogram.PropTypes = {
  data: PropTypes.arrayOf(
    PropTypes.shape({
      x: PropTypes.number.isRequired,
      y:PropTypes.number.isRequired,
    })
  ).isRequired
}

export default Histogram;
